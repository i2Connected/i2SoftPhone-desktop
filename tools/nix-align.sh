#!/usr/bin/env bash
# Copyright (C) 2010-2023 Belledonne Communications SARL
# SPDX-License-Identifier: AGPL-3.0-or-later
#
# Small helper script to align nix with submodules

set -euxo pipefail

git describe
nix flake update
nix build
