import React from 'react';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import { NavigationContainer } from '@react-navigation/native';
import HomeScreen from '../screens/HomeScreen';
import SettingsScreen from '../screens/SettingsScreen';
import { BOOLEAN_VALUES } from '../config'; // Updated import path for config.js

// Create a Bottom Tab Navigator
const Tab = createBottomTabNavigator();

// MainTabNavigator component to manage bottom tab navigation
export default function MainTabNavigator() {
    // Check if required screens are provided and valid
    if (!HomeScreen || typeof HomeScreen !== 'function') {
        console.error('HomeScreen component is missing or invalid.');
        return null;
    }

    if (!SettingsScreen || typeof SettingsScreen !== 'function') {
        console.error('SettingsScreen component is missing or invalid.');
        return null;
    }

    return (
        <NavigationContainer>
            <Tab.Navigator>
                {BOOLEAN_VALUES.SHOW_HOME_TAB && (
                    <Tab.Screen name="Home" component={HomeScreen} />
                )}
                {BOOLEAN_VALUES.SHOW_SETTINGS_TAB && (
                    <Tab.Screen name="Settings" component={SettingsScreen} />
                )}
            </Tab.Navigator>
        </NavigationContainer>
    );
}

/*
* This file defines the MainTabNavigator component, which sets up the bottom tab navigation for the app using React Navigation.
* 
* The component uses two screens:
* - 'HomeScreen': The main screen of the app.
* - 'SettingsScreen': The settings screen of the app.
* 
* If the required screens are not provided or invalid, errors will be logged to the console.
*
* Placeholders:
* - To add new tabs, import the new screen components at the top and add new Tab.Screen entries inside the Tab.Navigator.
* - To customize the appearance of the tabs, modify the Tab.Navigator and Tab.Screen props accordingly.
*
* Example of how to add a new tab:
* 
* 1. Import the new screen component:
* import ProfileScreen from '../screens/ProfileScreen';
* 
* 2. Add a new Tab.Screen entry inside the Tab.Navigator:
* <Tab.Screen name="Profile" component={ProfileScreen} />
* 
* This will add a new tab for the ProfileScreen component.
*/
