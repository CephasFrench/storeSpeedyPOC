import React from 'react';
import { SafeAreaView, StyleSheet, ScrollView, Text } from 'react-native';
import App from '../App';

// HomeScreen component to display the main application screen
export default function HomeScreen() {
    // Check if the App component is valid
    if (!App || typeof App !== 'function') {
        console.error('App component is missing or invalid.');
        return <Text style={styles.errorText}>Failed to load the application. Please try again later.</Text>;
    }

    return (
        <SafeAreaView style={styles.safeArea}>
            <ScrollView contentContainerStyle={styles.container}>
                <App />
            </ScrollView>
        </SafeAreaView>
    );
}

// Styles for the HomeScreen component
const styles = StyleSheet.create({
    safeArea: {
        flex: 1,
    },
    container: {
        flexGrow: 1,
    },
    errorText: {
        color: 'red',
        textAlign: 'center',
        marginTop: 20,
    },
});

/*
* This file defines the HomeScreen component, which serves as the main screen of the application.
* 
* The component uses the following elements:
* - 'SafeAreaView': Ensures that the content is rendered within the safe area boundaries of a device.
* - 'ScrollView': Allows the content to be scrollable if it overflows the screen size.
* - 'App': The main application component.
* 
* If the App component is not provided or invalid, an error message will be displayed.
*
* Style definitions are provided at the bottom of the file to maintain visual consistency.
*
* Placeholders:
* - To add new functionality or features, you can add new components inside the ScrollView.
* - To handle more complex interactions or state, update the HomeScreen component accordingly.
* - For additional styles, update the StyleSheet object as needed.
*
* Example of how to use this component:
* 
* <HomeScreen />
* 
* This component will render the main App component within a scrollable view and safe area.
*/

