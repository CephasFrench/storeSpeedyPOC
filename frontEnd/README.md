# StoreSpeedy Frontend

## Project Overview

This project is the frontend for StoreSpeedy, an application designed to help users navigate HEB stores efficiently. It is built using React Native and Expo. This document explains the file structure and details about each part of the project.

## File Structure

```plaintext
frontend/
├── assets/
│   └── ... (images, fonts, etc.)
├── components/
│   ├── AisleList.js
│   ├── GroceryList.js
│   ├── InputWithButton.js
│   └── ... (other reusable components)
├── navigation/
│   └── MainTabNavigator.js
├── screens/
│   ├── HomeScreen.js
│   ├── SettingsScreen.js
│   └── ... (other screens)
├── utils/
│   └── cookieManager.js
├── App.js
├── app.json
├── index.js
├── package-lock.json
├── package.json
└── ... (other configuration files)
```


### Folder and File Explanations

#### assets/
This folder contains static assets such as images, fonts, and other media files used throughout the application.

- **Usage**: Add images, fonts, and other static files here.

#### components/
This folder contains reusable UI components that can be used across different screens. Each component is designed to be modular and reusable.

- **AisleList.js**: Displays the list of aisles and the items in each aisle.
  - **Usage**: Use this component to display aisle information on any screen.

- **GroceryList.js**: Displays the list of grocery items the user has added.
  - **Usage**: Use this component to show the user's grocery list on any screen.

- **InputWithButton.js**: A reusable input field with a button for adding items.
  - **Usage**: Use this component wherever you need an input field with an accompanying button.

#### navigation/
This folder contains navigation configuration files. This is where you define the structure and behavior of the app's navigation.

- **MainTabNavigator.js**: Configures the main tab navigation of the app.
  - **Usage**: Modify this file to add or remove tabs from the main navigation.

#### screens/
This folder contains individual screens or pages of the application. Each file represents a different screen and typically composes several components.

- **HomeScreen.js**: The main screen of the app where users can add items and generate a route.
  - **Usage**: Modify this file to change the main functionality of the app's home screen.

- **SettingsScreen.js**: The settings screen where users can configure app preferences.
  - **Usage**: Add settings-related components and logic in this file.

#### utils/
This folder contains utility functions, helper methods, and services that can be used across the application.

- **cookieManager.js**: Manages cookies for the app.
  - **Usage**: Use this utility for handling cookies in different parts of the app.

#### App.js
The main entry point for the application. It sets up the root component and initializes navigation.

- **Usage**: This file is typically modified to set up global providers, configure navigation, or apply global styles.

#### app.json
Configuration file for the Expo project.

- **Usage**: Modify this file to change project settings like the name, icon, splash screen, and more.

#### index.js
The entry point for the React Native app. It registers the main component.

- **Usage**: This file is generally left unchanged unless you need to configure the app entry point differently.

#### package-lock.json & package.json
Configuration files for managing project dependencies.

- **Usage**: Modify `package.json` to add or update project dependencies. The `package-lock.json` file is generated automatically.

## Adding New Components

To add a new component:
1. Create a new file in the `components/` directory.
2. Define the component and its styles.
3. Export the component.
4. Import and use the component in the desired screen or other components.

## Adding New Screens

To add a new screen:
1. Create a new file in the `screens/` directory.
2. Define the screen component and its styles.
3. Add the screen to your navigation configuration in `navigation/MainTabNavigator.js`.

## Managing State and Data

- Use React's `useState` and `useEffect` hooks for managing local state and side effects.
- For global state management, consider using Context API or Redux.
- To fetch and update data, use JavaScript's `fetch` API or third-party libraries like Axios.

## Running the Project

To start the project, run the following commands:

```bash
# Start server, update dependencies, and run simulation:
./run_app.sh

# If a separate expo terminal does not start, run
npx expo start
