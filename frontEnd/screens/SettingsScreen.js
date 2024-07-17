import React from 'react';
import { View, Text, StyleSheet, Alert, Switch, SafeAreaView, ScrollView, TouchableOpacity } from 'react-native';

export default function SettingsScreen() {
    const [notificationsEnabled, setNotificationsEnabled] = React.useState(false);

    const toggleNotifications = () => {
        setNotificationsEnabled(!notificationsEnabled);
    };

    // Function to handle server ping
    const handlePingServer = () => {
        fetch('http://localhost:8080/ping')
            .then((response) => {
                if (!response.ok) {
                    throw new Error(`HTTP error! status: ${response.status}`);
                }
                Alert.alert("Success", "Server communication successful.");
            })
            .catch((error) => {
                console.error('Error pinging server:', error);
                Alert.alert("Error", "Failed to communicate with server.");
            });
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
                <TouchableOpacity style={styles.button} onPress={handlePingServer}>
                    <Text style={styles.buttonText}>Ping Server</Text>
                </TouchableOpacity>
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
    button: {
        backgroundColor: '#ff0000',
        padding: 15,
        borderRadius: 5,
        marginBottom: 20,
        alignItems: 'center',
    },
    buttonText: {
        color: '#ffffff',
        fontSize: 16,
    },
});
