{
  description = "Linphone Qt Desktop Client";

  inputs = {
    linphone-sdk = {
      url = git+file:./linphone-sdk;
      inputs = {
        nixpkgs.follows = "nixpkgs";
        bctoolbox-src.url = git+file:./linphone-sdk/bctoolbox;
        bcunit-src.url = git+file:./linphone-sdk/bcunit;
        belcard-src.url = git+file:./linphone-sdk/belcard;
        belle-sip-src.url = git+file:./linphone-sdk/belle-sip;
        belr-src.url = git+file:./linphone-sdk/belr;
        bzrtp-src.url = git+file:./linphone-sdk/bzrtp;
        decaf-src.url = git+file:./linphone-sdk/external/decaf;
        lime-src.url = git+file:./linphone-sdk/lime;
        liblinphone-src.url = git+file:./linphone-sdk/liblinphone;
        mediastreamer2-src.url = git+file:./linphone-sdk/mediastreamer2;
        msopenh264-src.url = git+file:./linphone-sdk/msopenh264;
        ortp-src.url = git+file:./linphone-sdk/ortp;
        soci-src.url = git+file:./linphone-sdk/external/soci;
      };
    };
    ispell-src = {
      url = git+file:./external/ispell;
      flake = false;
    };
  };

  outputs = { self, nixpkgs, linphone-sdk, ispell-src, ... }: {

    overlays.default = final: prev: {
      
      chore = {
        update-from-submodules = prev.stdenv.mkDerivation rec {
          name = "update-from-submodules";
          src = ./tools/nix-align.sh;
          unpackPhase = "true";
          buildPhase = "true";
          installPhase = "mkdir -p $out/bin; cp $src $out/bin/$name";
        };
      };

      linphone = prev.linphone.overrideAttrs (attrs:
        let overriddenSrc = linphone-sdk.nixUtils.overrideSource self; in
        overriddenSrc // {
          buildInputs = [
            final.bctoolbox
            final.lime
            final.liblinphone
            final.mediastreamer
            final.belcard
            final.belr
            final.belle-sip

            final.jsoncpp
          ] ++ (with final.libsForQt5; [
            qtkeychain
            qtquickcontrols2
            qtmultimedia
            qtspeech
            poppler
          ]);

          # Manually copy submodule source to where it's expected to be
          postUnpack = ''
            ispell_dir=$NIX_BUILD_TOP/source/external/ispell/
            mkdir --parents $ispell_dir
            cp --no-preserve=mode --recursive ${ispell-src}/* $ispell_dir
          '';

          # Disable upstream (nixpkgs) patches
          patches = [ ];
          postPatch = '''';

          postInstall = with final; ''
            # I would like to set LINPHONEAPP_INSTALL_PREFIX but then compilation fails when trying to include <LinphoneApp/LinphonePlugin.hpp>
            mv --target-directory=$out ./OUTPUT/*

            mkdir -p $out/share/belr/grammars
            ln -s ${liblinphone}/share/belr/grammars/* $out/share/belr/grammars/
            ln -s ${belle-sip}/share/belr/grammars/* $out/share/belr/grammars/

            mkdir -p $out/lib/mediastreamer/plugins
            ln -s ${mediastreamer-openh264}/lib/mediastreamer/plugins/* $out/lib/mediastreamer/plugins/
            ln -s ${mediastreamer}/lib/mediastreamer/plugins/* $out/lib/mediastreamer/plugins/

            cp linphone-app/libapp-plugin.so $out/lib/

            wrapProgram $out/bin/linphone \
              --set MEDIASTREAMER_PLUGINS_DIR \
                    $out/lib/mediastreamer/plugins
          '';

          cmakeFlags = attrs.cmakeFlags ++ [
            # Do not build the SDK
            "-DLINPHONE_QT_ONLY=YES"
            "-DENABLE_BUILD_APP_PLUGINS=NO"
            "-DENABLE_UPDATE_CHECK=NO"
            "-DQTKEYCHAIN_TARGET_NAME=qt5keychain"
            (
              let datetime = overriddenSrc.version; in
              "-DLINPHONEAPP_VERSION=${builtins.substring 0 4 datetime}.${builtins.substring 4 2 datetime}.${builtins.substring 6 2 datetime}"
            )
            "-DFULL_VERSION=${overriddenSrc.version}-nix"
            "-DLINPHONE_OUTPUT_DIR=${final.liblinphone}"
            #"-DISPELL_OUTPUT_DIR=${final.ispell}"
          ];
        });

        ispell = prev.ispell.overrideAttrs (attrs: (linphone-sdk.nixUtils.overrideSource ispell-src) // {
          nativeBuildInputs = [ final.cmake ];
        });
    };

    packages.x86_64-linux = import nixpkgs {
      system = "x86_64-linux";
      overlays = [
        linphone-sdk.overlays.default
        self.overlays.default
      ];
    };

    defaultPackage.x86_64-linux = self.packages.x86_64-linux.linphone;

    apps.x86_64-linux.default = {
      type = "app";
      program = "${self.packages.x86_64-linux.linphone}/bin/linphone";
    };

  };
}
