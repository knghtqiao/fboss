/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include "fboss/agent/platforms/wedge/WedgePort.h"
#include "fboss/agent/gen-cpp2/switch_config_types.h"

namespace facebook { namespace fboss {


class GalaxyPort : public WedgePort {
 public:
  GalaxyPort(PortID id,
             WedgePlatform* platform,
             folly::Optional<TransceiverID> frontPanelPort,
             folly::Optional<ChannelID> channel,
             const XPEs& egressXPEs) :
      WedgePort(id, platform, frontPanelPort, channel, egressXPEs) {}

  LaneSpeeds supportedLaneSpeeds() const override {
    LaneSpeeds speeds;
    speeds.insert(cfg::PortSpeed::GIGE);
    speeds.insert(cfg::PortSpeed::XG);
    speeds.insert(cfg::PortSpeed::TWENTYFIVEG);
    return speeds;
  }

  void prepareForGracefulExit() override {}
  void linkStatusChanged(bool up, bool adminUp) override;
  bool isBackplanePort() const {
    return !frontPanelPort_.hasValue();
  }
  bool shouldDisableFEC() const override {
    // Only disable FEC if this is a backplane port
    return isBackplanePort();
  }
};

}} // facebook::fboss
