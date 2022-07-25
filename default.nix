let
  linphone_overlay = self: super: {
    linphone = super.linphone.overrideAttrs (old: {
      src = ./.;
      postPatch = old.postPatch + ''
        echo "set(FULL_VERSION ${old.version})" >> linphone-app/linphoneqt_version.cmake
      '';
    });
    liblinphone = super.liblinphone.overrideAttrs (old: {
      src = ./linphone-sdk/liblinphone;
    });
    mediastreamer = super.mediastreamer.overrideAttrs (old: {
      src = ./linphone-sdk/mediastreamer2;
    });
    ortp = super.ortp.overrideAttrs (old: {
      src = ./linphone-sdk/ortp;
    });
    bctoolbox = super.bctoolbox.overrideAttrs (old: {
      src = ./linphone-sdk/bctoolbox;
    });
    belle-sip = super.belle-sip.overrideAttrs (old: {
      src = ./linphone-sdk/belle-sip;
    });
    bzrtp = super.bzrtp.overrideAttrs (old: {
      src = ./linphone-sdk/bzrtpbelle-sip;
    });
  };
in

{ pkgs ? import <nixpkgs> { overlays = [ linphone_overlay ]; }
}:

pkgs.linphone
