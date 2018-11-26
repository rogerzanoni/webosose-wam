// Copyright (c) 2012-2018 LG Electronics, Inc.
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

#include "PalmSystemBase.h"

#include <sstream>
#include <boost/filesystem.hpp>

#include "LogManager.h"
#include "WebAppManager.h"
#include "WebAppManagerUtils.h"

std::string PalmSystemBase::getDeviceInfo(const std::string& name)
{
    std::string value;
    WebAppManager::instance()->getDeviceInfo(name, value);

    return value;
}

QVariant PalmSystemBase::getResource(QVariant a, QVariant b) // FIXME: PalmSystem: qvariant-less
{
    boost::filesystem::path p(a.toString().toStdString());
    std::string data;

    try {
        WebAppManagerUtils::readFileContent(p.string(), data);
    } catch (const std::exception &e) {
        LOG_DEBUG("PalmSystemBase: Failed to read resource '%s' due to error '%s'.",
                  p.string().c_str(), e.what());
    }

    return QVariant(data.c_str());
}

std::string PalmSystemBase::country() const
{
    std::string localcountry;
    std::string smartServiceCountry;

    WebAppManager::instance()->getDeviceInfo("LocalCountry", localcountry);
    WebAppManager::instance()->getDeviceInfo("SmartServiceCountry", smartServiceCountry);

    std::stringstream jss;
    jss << "{ \"country\": \"" << localcountry
        << "\", \"smartServiceCountry\": \"" << smartServiceCountry << "\" }";

    return jss.str();
}

std::string PalmSystemBase::locale() const
{
    std::string systemlocale;
    WebAppManager::instance()->getSystemLanguage(systemlocale);
    return systemlocale;
}

std::string PalmSystemBase::localeRegion() const
{
    return "US";
}

std::string PalmSystemBase::phoneRegion() const
{
    return {};
}

void PalmSystemBase::setContainerAppReady(const std::string& appId)
{
    if (appId == WebAppManager::instance()->getContainerAppId())
        WebAppManager::instance()->setContainerAppReady(true);
}
