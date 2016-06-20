//
//  DomainServerSettingsManager.h
//  domain-server/src
//
//  Created by Stephen Birarda on 2014-06-24.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_DomainServerSettingsManager_h
#define hifi_DomainServerSettingsManager_h

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>

#include <HifiConfigVariantMap.h>
#include <HTTPManager.h>

#include <ReceivedMessage.h>
#include "NodePermissions.h"

const QString SETTINGS_PATHS_KEY = "paths";

const QString SETTINGS_PATH = "/settings";
const QString SETTINGS_PATH_JSON = SETTINGS_PATH + ".json";
const QString AGENT_STANDARD_PERMISSIONS_KEYPATH = "security.standard_permissions";
const QString AGENT_PERMISSIONS_KEYPATH = "security.permissions";
const QString GROUP_PERMISSIONS_KEYPATH = "security.group_permissions";

class DomainServerSettingsManager : public QObject {
    Q_OBJECT
public:
    DomainServerSettingsManager();
    bool handlePublicHTTPRequest(HTTPConnection* connection, const QUrl& url);
    bool handleAuthenticatedHTTPRequest(HTTPConnection* connection, const QUrl& url);

    void setupConfigMap(const QStringList& argumentList);
    QVariant valueOrDefaultValueForKeyPath(const QString& keyPath);

    QVariantMap& getUserSettingsMap() { return _configMap.getUserConfig(); }
    QVariantMap& getSettingsMap() { return _configMap.getMergedConfig(); }

    bool haveStandardPermissionsForName(const QString& name) const { return _standardAgentPermissions.contains(name); }
    NodePermissions getStandardPermissionsForName(const QString& name) const;

    bool havePermissionsForName(const QString& name) const { return _agentPermissions.contains(name); }
    NodePermissions getPermissionsForName(const QString& name) const;
    QStringList getAllNames() { return _agentPermissions.keys(); }

    bool havePermissionsForGroup(const QString& groupname) const { return _groupPermissions.contains(groupname); }
    NodePermissions getPermissionsForGroup(const QString& groupname) const;
    NodePermissions getPermissionsForGroup(const QUuid& groupID) const;
    QList<QUuid> getKnownGroupIDs() { return _groupByID.keys(); }

    // these are used to locally cache the result of calling "api/v1/groups/%1/is_member/%2" on metaverse's api
    void recordGroupMembership(const QString& name, const QUuid groupID, bool isMember);
    bool isGroupMember(const QString& name, const QUuid& groupID);

signals:
    void updateNodePermissions();

public slots:
    void getGroupIDJSONCallback(QNetworkReply& requestReply);
    void getGroupIDErrorCallback(QNetworkReply& requestReply);

private slots:
    void processSettingsRequestPacket(QSharedPointer<ReceivedMessage> message);

private:
    QStringList _argumentList;

    QJsonObject responseObjectForType(const QString& typeValue, bool isAuthenticated = false);
    bool recurseJSONObjectAndOverwriteSettings(const QJsonObject& postedObject);

    void updateSetting(const QString& key, const QJsonValue& newValue, QVariantMap& settingMap,
                       const QJsonObject& settingDescription);
    QJsonObject settingDescriptionFromGroup(const QJsonObject& groupObject, const QString& settingName);
    void sortPermissions();
    void persistToFile();

    double _descriptionVersion;
    QJsonArray _descriptionArray;
    HifiConfigVariantMap _configMap;

    friend class DomainServer;

    void requestMissingGroupIDs();
    void getGroupID(const QString& groupname);
    NodePermissionsPointer lookupGroupByID(const QUuid& id);

    void packPermissionsForMap(QString mapName, NodePermissionsMap& agentPermissions, QString keyPath);
    void packPermissions();
    void unpackPermissions();
    NodePermissionsMap _standardAgentPermissions; // anonymous, logged-in, localhost
    NodePermissionsMap _agentPermissions; // specific account-names
    NodePermissionsMap _groupPermissions; // permissions granted by membershipt to specific groups
    QHash<QUuid, NodePermissionsPointer> _groupByID;
    QHash<QString, QHash<QUuid, bool>> _groupMembership;
};

#endif // hifi_DomainServerSettingsManager_h
