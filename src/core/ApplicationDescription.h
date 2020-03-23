// Copyright (c) 2008-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef APPLICATIONDESCRIPTION_H
#define APPLICATIONDESCRIPTION_H

#include <memory>
#include <unordered_map>
#include <set>
#include <string>

#include "DisplayId.h"

class ApplicationDescription {
public:
    enum WindowClass {
        WindowClass_Normal = 0x00,
        WindowClass_Hidden = 0x01
    };

    ApplicationDescription();
    virtual ~ApplicationDescription() {}

    const std::string& id() const { return m_id; }
    const std::string& title() const { return m_title; }
    const std::string& entryPoint() const { return m_entryPoint; }
    const std::string& icon() const { return m_icon; }

    bool isTransparent() const
    {
        return m_transparency;
    }

    bool handlesDeeplinking() const
    {
        return !m_deeplinkingParams.empty();
    }

    bool handlesRelaunch() const
    {
        return m_handlesRelaunch;
    }

    const std::string& vendorExtension() const
    {
        return m_vendorExtension;
    }

    WindowClass windowClassValue() const { return m_windowClassValue; }

    const std::string& trustLevel() const
    {
        return m_trustLevel;
    }

    const std::string& subType() const
    {
        return m_subType;
    }

    const std::string& folderPath() const
    {
        return m_folderPath;
    }

    const std::string& defaultWindowType() const
    {
        return m_defaultWindowType;
    }

    const std::string& enyoBundleVersion() const
    {
        return m_enyoBundleVersion;
    }

    const std::set<std::string>& supportedEnyoBundleVersions() const
    {
        return m_supportedEnyoBundleVersions;
    }

    const std::string& enyoVersion() const
    {
        return m_enyoVersion;
    }

    const std::string& version() const
    {
        return m_version;
    }

    const std::string& groupWindowDesc() const
    {
        return m_groupWindowDesc;
    }

    const std::string& v8SnapshotPath() const
    {
        return m_v8SnapshotPath;
    }

    const std::string& v8ExtraFlags() const
    {
        return m_v8ExtraFlags;
    }

    static std::unique_ptr<ApplicationDescription> fromJsonString(const char* jsonStr);

    bool isInspectable() const { return m_inspectable; }
    bool useCustomPlugin() const { return m_customPlugin; }
    bool useNativeScroll() const { return m_useNativeScroll; }
    bool usePrerendering() const { return m_usePrerendering; }

    bool doNotTrack() const { return m_doNotTrack; }

    bool backHistoryAPIDisabled() const { return m_backHistoryAPIDisabled; }
    void setBackHistoryAPIDisabled(bool disabled) { m_backHistoryAPIDisabled = disabled; }

    int widthOverride() const { return m_widthOverride; }
    int heightOverride() const { return m_heightOverride; }

    bool handleExitKey() const { return m_handleExitKey; }
    bool supportsAudioGuidance() const { return m_supportsAudioGuidance; }
    bool isEnableBackgroundRun() const { return m_enableBackgroundRun; }
    bool allowVideoCapture() const { return m_allowVideoCapture; }
    bool allowAudioCapture() const { return m_allowAudioCapture; }

    virtual bool useVirtualKeyboard() const { return m_useVirtualKeyboard; }
    //Key code is changed only for facebooklogin WebApp
    const std::unordered_map<int, std::pair<int, int>>& keyFilterTable() const
    {
        return m_keyFilterTable;
    }

    double networkStableTimeout() const { return m_networkStableTimeout; }
    bool disallowScrollingInMainFrame() const { return m_disallowScrollingInMainFrame; }
    int delayMsForLaunchOptimization() const { return m_delayMsForLanchOptimization; }
    bool useUnlimitedMediaPolicy() const { return m_useUnlimitedMediaPolicy; }
    const std::string& locationHint() const { return m_locationHint; }

    int surfaceRole() const { return m_surface_role; }
    int panelType() const { return m_panel_type; }

    struct WindowOwnerInfo {
        WindowOwnerInfo()
            : allowAnonymous(false)
        {
        }

        bool allowAnonymous;
        std::unordered_map<std::string, int> layers;
    };

    struct WindowClientInfo {
        std::string layer;
        std::string hint;
    };

    struct WindowGroupInfo {
        WindowGroupInfo()
            : isOwner(false)
        {
        }

        std::string name;
        bool isOwner;
    };

    const WindowGroupInfo getWindowGroupInfo();
    const WindowOwnerInfo getWindowOwnerInfo();
    const WindowClientInfo getWindowClientInfo();

    // To support multi display
    DisplayId getDisplayAffinity() { return m_displayAffinity; }
    void setDisplayAffinity(DisplayId display) { m_displayAffinity = display; }
    int customSuspendDOMTime() const { return m_customSuspendDOMTime; }
    std::string mediaPreferences() const { return m_mediaPreferences; }
    int surfaceId() { return m_surfaceId; }

private:
    std::string m_id;
    std::string m_title;
    std::string m_entryPoint;
    std::string m_icon;
    std::string m_requestedWindowOrientation;

    bool m_transparency;
    std::string m_vendorExtension;
    WindowClass m_windowClassValue;
    std::string m_trustLevel;
    std::string m_subType;
    std::string m_deeplinkingParams;
    bool m_handlesRelaunch;
    std::string m_folderPath;
    std::string m_defaultWindowType;
    std::string m_enyoBundleVersion;
    std::set<std::string> m_supportedEnyoBundleVersions;
    std::string m_enyoVersion;
    std::string m_version;
    std::string m_v8SnapshotPath;
    std::string m_v8ExtraFlags;
    bool m_inspectable;
    bool m_customPlugin;
    bool m_backHistoryAPIDisabled;
    int m_widthOverride;
    int m_heightOverride;
    std::unordered_map<int, std::pair<int, int>> m_keyFilterTable;
    std::string m_groupWindowDesc;
    bool m_doNotTrack;
    bool m_handleExitKey;
    bool m_enableBackgroundRun;
    bool m_allowVideoCapture;
    bool m_allowAudioCapture;
    bool m_supportsAudioGuidance;
    bool checkTrustLevel(std::string trustLevel);
    bool m_useNativeScroll;
    bool m_usePrerendering;
    double m_networkStableTimeout;
    bool m_disallowScrollingInMainFrame;
    int m_delayMsForLanchOptimization;
    bool m_useUnlimitedMediaPolicy;
    int m_displayAffinity;
    std::string m_locationHint;
    bool m_useVirtualKeyboard;
    int m_customSuspendDOMTime;
    std::string m_mediaPreferences;
    int m_surfaceId;

    int m_surface_role;
    int m_panel_type;
};

#endif /* APPLICATIONDESCRIPTION_H */
