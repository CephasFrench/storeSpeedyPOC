import React, { useState, useEffect } from 'react';
import { View, Text, StyleSheet, Alert, Switch, SafeAreaView, ScrollView, TouchableOpacity } from 'react-native';
import * as SecureStore from 'expo-secure-store';
import { BOOLEAN_VALUES } from '../config'; // Corrected relative path

// SettingsScreen component to manage application settings
export default function SettingsScreen() {
    const [notificationsEnabled, setNotificationsEnabled] = useState(false);
    const [isDeveloper, setIsDeveloper] = useState(BOOLEAN_VALUES.DEVELOPER_MODE);

    useEffect(() => {
        // Fetch developer mode from secure storage
        const fetchDeveloperMode = async () => {
            const storedIsDeveloper = await SecureStore.getItemAsync('isDeveloper');
            setIsDeveloper(storedIsDeveloper === 'true');
        };

        fetchDeveloperMode();
    }, []);

    // Toggle notifications setting
    const toggleNotifications = () => {
        setNotificationsEnabled(!notificationsEnabled);
    };

    // Toggle developer mode setting
    const toggleDeveloperMode = async () => {
        const newIsDeveloper = !isDeveloper;
        setIsDeveloper(newIsDeveloper);
        await SecureStore.setItemAsync('isDeveloper', newIsDeveloper.toString());
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
                {BOOLEAN_VALUES.SHOW_NOTIFICATIONS_TOGGLE && (
                    <View style={styles.setting}>
                        <Text style={styles.settingText}>Enable Notifications</Text>
                        <Switch
                            value={notificationsEnabled}
                            onValueChange={toggleNotifications}
                        />
                    </View>
                )}
                <View style={styles.setting}>
                    <Text style={styles.settingText}>Developer Mode</Text>
                    <Switch
                        value={isDeveloper}
                        onValueChange={toggleDeveloperMode}
                    />
                </View>
                <TouchableOpacity style={styles.button} onPress={handlePingServer}>
                    <Text style={styles.buttonText}>Ping Server</Text>
                </TouchableOpacity>
            </ScrollView>
        </SafeAreaView>
    );
}

// Styles for the SettingsScreen component
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
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});

/*
* This file defines the SettingsScreen component, which manages application settings.
* 
* The component includes the following elements:
* - 'SafeAreaView': Ensures that the content is rendered within the safe area boundaries of a device.
* - 'ScrollView': Allows the content to be scrollable if it overflows the screen size.
* - 'Text': Displays the title of the settings screen.
* - 'View': Groups settings elements.
* - 'Switch': Toggles the notifications and developer mode settings.
* - 'TouchableOpacity': Button to ping the server.
* 
* If there is an error in pinging the server, an alert message will be displayed.
*
* Style definitions are provided at the bottom of the file to maintain visual consistency.
*
* Placeholders:
* - To add new settings, create new 'View' elements similar to the notifications setting.
* - To handle more complex interactions or state, update the SettingsScreen component accordingly.
* - For additional styles, update the StyleSheet object as needed.
*
* Example of how to use this component:
* 
* <SettingsScreen />
* 
* This component will render the settings screen with the ability to toggle notifications, developer mode, and ping the server.
*/
