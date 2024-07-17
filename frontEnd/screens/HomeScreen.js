import React from 'react';
import { SafeAreaView, StyleSheet, ScrollView } from 'react-native';
import App from '../App';

export default function HomeScreen() {
    return (
        <SafeAreaView style={styles.safeArea}>
            <ScrollView contentContainerStyle={styles.container}>
                <App />
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
    },
});