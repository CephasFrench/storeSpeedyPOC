import React from 'react';
import { View, Text, StyleSheet, Switch, SafeAreaView, ScrollView } from 'react-native';

export default function SettingsScreen() {
    const [notificationsEnabled, setNotificationsEnabled] = React.useState(false);

    const toggleNotifications = () => {
        setNotificationsEnabled(!notificationsEnabled);
    };

    return (
        <SafeAreaView style={styles.safeArea}>
            <ScrollView contentContainerStyle={styles.container}>
                <Text style={styles.text}>Settings</Text>
                <View style={styles.setting}>
                    <Text style={styles.settingText}>Enable Notifications</Text>
                    <Switch
                        value={notificationsEnabled}
                        onValueChange={toggleNotifications}
                    />
                </View>
            </ScrollView>
        </SafeAreaView>
    );
}

const styles = StyleSheet.create({
    safeArea: {
        flex: 1,
    },
    container: {
        flexGrow: 1,
        padding: 20,
    },
    text: {
        fontSize: 18,
        color: '#1d3557',
        marginBottom: 20,
    },
    setting: {
        flexDirection: 'row',
        justifyContent: 'space-between',
        alignItems: 'center',
        marginBottom: 20,
    },
    settingText: {
        fontSize: 16,
        color: '#1d3557',
    },
});