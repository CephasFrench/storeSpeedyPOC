# Project File Structure:

```
STORESPEEDYPOC/
├── .expo/
├── .vscode/
├── backEnd/
│   ├── build/
│   ├── server/
│   │   ├── Crow/
│   │   ├── storage/
│   │   │   ├── locations/
│   │   │   │   ├── DefaultLoc/
│   │   │   │   ├── ValleyMillsWaco/
│   │   │   ├── users/
│   │   │       ├── cam/
│   │   │       ├── default/
│   ├── src/
│   │   ├── aisles/
│   │   │   ├── aisle.cpp
│   │   │   ├── aisle.h
│   │   ├── api/
│   │   │   ├── api_util.cpp
│   │   │   ├── api_util.h
│   │   ├── build/
│   │   ├── cart/
│   │   │   ├── cart.cpp
│   │   │   ├── cart.h
│   │   ├── items/
│   │       ├── build_and_run.sh
│   │       ├── Item.cpp
│   │       ├── Item.h
│   │       ├── itemTesting.cpp
│   ├── build.sh
│   ├── CMakeLists.txt
│   ├── config.h
│   ├── crow_all.h
│   ├── infoForCam.txt
│   ├── main.cpp
│   ├── package-lock.json
│   ├── StoreSpeedyJsonHandler.cpp
│   ├── StoreSpeedyJsonHandler.h
│   ├── itemDatabase.cpp
├── Devmode/
├── files/
├── frontEnd/
│   ├── .expo/
│   ├── assets/
│   ├── components/
│   │   ├── AisleList.js
│   │   ├── GroceryList.js
│   │   ├── InputWithButton.js
│   ├── navigation/
│   │   ├── MainTabNavigator.js
│   ├── node_modules/
│   ├── screens/
│   │   ├── HomeScreen.js
│   │   ├── SettingsScreen.js
│   ├── utils/
│   │   ├── api.js
│   │   ├── cookieManager.js
│   ├── App.js
│   ├── app.json
│   ├── config.js
│   ├── index.js
│   ├── package-lock.json
│   ├── package.json
│   ├── README.md
├── .gitignore
├── info for other distributions.txt
├── package-lock.json
├── README.md
├── run_app.sh
```

# Potential file structure after added Features:

```
STORESPEEDYPOC/
├── .expo/
├── .vscode/
├── backEnd/
│   ├── build/
│   ├── server/
│   │   ├── Crow/
│   │   ├── storage/
│   │   │   ├── locations/
│   │   │   │   ├── DefaultLoc/
│   │   │   │   ├── ValleyMillsWaco/
│   │   │   ├── users/
│   │   │       ├── cam/
│   │   │       ├── default/
│   ├── src/
│   │   ├── aisles/
│   │   │   ├── aisle.cpp
│   │   │   ├── aisle.h
│   │   ├── api/
│   │   │   ├── api_util.cpp
│   │   │   ├── api_util.h
│   │   ├── build/
│   │   ├── cart/
│   │   │   ├── cart.cpp
│   │   │   ├── cart.h
│   │   ├── items/
│   │   │   ├── build_and_run.sh
│   │   │   ├── Item.cpp
│   │   │   ├── Item.h
│   │   │   ├── itemTesting.cpp
│   │   ├── notifications/          <-- New folder for notification-related features
│   │   │   ├── out_of_stock.cpp
│   │   │   ├── item_expiration.cpp
│   │   │   ├── donation_integration.cpp
│   │   ├── suggestions/            <-- New folder for AI and recommendation features
│   │   │   ├── ai_tips.cpp
│   │   │   ├── bulk_purchase.cpp
│   │   │   ├── smart_substitutions.cpp
│   │   │   ├── recipe_suggestions.cpp
│   ├── build.sh
│   ├── CMakeLists.txt
│   ├── config.h
│   ├── crow_all.h
│   ├── infoForCam.txt
│   ├── main.cpp
│   ├── package-lock.json
│   ├── StoreSpeedyJsonHandler.cpp
│   ├── StoreSpeedyJsonHandler.h
│   ├── itemDatabase.cpp
├── Devmode/
├── files/
├── frontEnd/
│   ├── .expo/
│   ├── assets/
│   ├── components/
│   │   ├── AisleList.js
│   │   ├── GroceryList.js
│   │   ├── InputWithButton.js
│   │   ├── FavoriteItems.js            <-- New component for favorite items
│   │   ├── DealsCoupons.js             <-- New component for deals and coupons
│   │   ├── DietaryAlerts.js            <-- New component for dietary restrictions / allergen alerts
│   │   ├── Notifications.js            <-- New component for notifications (e.g., out of stock, expiration alerts)
│   │   ├── LoyaltyProgram.js           <-- New component for loyalty program integration
│   │   ├── CurbsideScheduling.js       <-- New component for curbside scheduling
│   │   ├── DonationCharity.js          <-- New component for donation/charity integration
│   │   ├── AppIncentives.js            <-- New component for gamification
│   │   ├── NutritionistIntegration.js  <-- New component for nutritionist/doctor integration
│   │   ├── BulkPurchase.js             <-- New component for bulk purchase recommendations
│   │   ├── Budgeting.js                <-- New component for budgeting
│   │   ├── AIFlavorPairing.js          <-- New component for AI flavor pairing
│   │   ├── LocalProduceTagging.js      <-- New component for local produce tagging
│   │   ├── VoiceSearchNavigation.js    <-- New component for voice search and navigation
│   ├── navigation/
│   │   ├── MainTabNavigator.js
│   ├── node_modules/
│   ├── screens/
│   │   ├── HomeScreen.js
│   │   ├── SettingsScreen.js
│   ├── utils/
│   │   ├── api.js
│   │   ├── cookieManager.js
│   │   ├── NotificationUtil.js     <-- New utility for handling notifications
│   │   ├── DietaryUtil.js          <-- New utility for dietary restrictions and allergen alerts
│   │   ├── RecommendationUtil.js   <-- New utility for AI-based recommendations
│   │   ├── LoyaltyUtil.js          <-- New utility for loyalty program integration
│   │   ├── BudgetingUtil.js        <-- New utility for budgeting
│   │   ├── FlavorPairingUtil.js    <-- New utility for AI flavor pairing
│   │   ├── ProduceTaggingUtil.js   <-- New utility for local produce tagging
│   ├── App.js
│   ├── app.json
│   ├── config.js
│   ├── index.js
│   ├── package-lock.json
│   ├── package.json
│   ├── README.md
├── .gitignore
├── info for other distributions.txt
├── package-lock.json
├── README.md
├── run_app.sh
```

# storeSpeedyPOC SPRINT Plan

json:
give gemini the first pdf page (aisles and whats on them) and give it the cart (items)
Have it return specific list of aisles and items on the aisle

## PETER TODO 2 WEEKS
- ~~Github set up~~
- Maze find the distance from each node to each other node
- Storing maze data
- ~~Setting up server~~
- Integrate all components

## CAM TODO 2 WEEKS
- ~~Expo and React~~
- ~~Shopping cart Object hierarchy~~
- ~~API calls to Gemini and JSON parsing~~

## Sprint 1: Frontend Development
**Dates:** July 3 - July 9

### Goals:
- ~~Set up the frontend environment with Expo and React Native.~~ - CAM
- Develop the shopping cart management system. - CAM
- ~~Create a basic user interface.~~ - CAM

### Tasks:
#### Project Initialization (July 3 - July 4)
- ~~Set up the React Native project with Expo.~~
- ~~Configure the project structure and dependencies.~~

#### Shopping Cart Management (July 5 - July 6)
- ~~Design and implement the object hierarchy for multiple shopping carts.~~
- Create components for adding, removing, and viewing cart items.

#### Basic User Interface (July 7 - July 8)
- Develop the initial user interface for managing shopping lists.
- Implement basic navigation between screens.

#### Review and Adjustments (July 9)
- Review the completed tasks.
- Make necessary adjustments based on initial testing and feedback.

## Sprint 2: Backend Development
**Dates:** July 10 - July 16

### Goals:
- ~~Set up the C++ server with Crow.~~
- Implement distance calculation and shortest path algorithms.

### Tasks:
#### Server Setup (July 10 - July 11) - PETER
- ~~Set up the C++ server with the Crow library.~~
- Create basic endpoints to handle requests from the frontend.

#### Distance Calculation (July 12 - July 13) - PETER
- Develop algorithms to calculate distances between items/nodes.
- Store distance information in a table for quick reference.

#### Shortest Path Calculation (July 14 - July 15) - PETER
- Implement algorithms to find the shortest path through the store.
- Optimize pathfinding algorithms for performance and accuracy.

#### Review and Adjustments (July 16)
- Review the backend components.
- Make necessary adjustments based on initial testing and feedback.

## Sprint 3: API Integration and Additional Features
**Dates:** July 17 - July 23

### Goals:
- ~~Integrate the Gemini API using Curl and Jsoncpp.~~
- Implement multithreading and developer tools.

### Tasks:
#### API Integration (July 17 - July 18)
- ~~Implement API calls to the Gemini API using Curl.~~
- Parse JSON responses using Jsoncpp.

#### Multithreading (July 19 - July 20)
- Implement multithreading to handle multiple requests.
- Ensure thread safety and optimal resource management.

#### Developer Tools (July 21 - July 22)
- Develop tools for monitoring and debugging backend processes.
- Implement features to display processing steps and performance metrics.

#### Review and Adjustments (July 23)
- Review the API integration and additional features.
- Make necessary adjustments based on testing and feedback.

## Sprint 4: Integration and Optimization
**Dates:** July 24 - July 30

### Goals:
- Integrate all components and perform thorough testing.
- Optimize the system for performance and usability.

### Tasks:
#### Component Integration (July 24 - July 25)
- Integrate the frontend and backend components.
- Ensure seamless communication between the frontend and backend.

#### User Interface Enhancements (July 26 - July 27)
- Improve the user interface for managing shopping lists.
- Add features to display the calculated shortest path through the store.

#### Testing and Bug Fixing (July 28 - July 29)
- Conduct thorough testing of the integrated system.
- Identify and fix any bugs or issues.

#### Optimization and Final Adjustments (July 30)
- Optimize the system for performance and usability.
- Make final adjustments based on feedback and testing results.

## Sprint 5: Deployment Preparation
**Dates:** July 31 - August 2

### Goals:
- Prepare the project for deployment.
- Ensure all documentation is up-to-date.

### Tasks:
#### Final Review and Adjustments (July 31)
- Conduct a final review of the project.
- Make any last-minute adjustments.

#### Documentation (August 1)
- Ensure all documentation is comprehensive and up-to-date.
- Prepare deployment guides and user manuals.

#### Deployment (August 2)
- Prepare the project for deployment.
- Deploy the application and ensure it is functioning as expected.
