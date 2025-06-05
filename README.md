# Country Data Analyzer

## 📌 Project Overview

This C++ project performs data processing and analysis for countries using a CSV dataset. The dataset includes information like:

- Country name
- Population
- Income
- Annual rainfall
- Graph connectivity (distance between countries)

The program reads and stores data in various structures like:
- **Doubly Linked List**
- **Max Heap** (for sorting rainfall)
- **Binary Search Tree (BST)** (for population-based sorting)
- **Adjacency Matrix** (for graph traversal)

It also performs graph-based algorithms like:
- **Dijkstra's Algorithm** for shortest path
- **Prim's Algorithm** for Minimum Spanning Tree (MST)

---

## 🔧 Features

- 📥 Read country data from CSV
- 🧱 Build a doubly linked list of countries
- 🌧️ Sort countries by rainfall using a Max Heap
- 👨‍👩‍👧‍👦 Sort countries by population using a Binary Search Tree (BST)
- 🗺️ Represent country distances using a 2D graph (adjacency matrix)
- 📍 Find shortest paths between countries using Dijkstra's algorithm
- 🛣️ Build minimum spanning trees using Prim’s algorithm

---

## 📁 CSV Format Assumption


- First row is headers
- Last 3 columns are: `Population`, `Income`, `Rainfall`
- Intermediate columns represent graph distances between cities (used in the adjacency matrix)

---

## 🚀 How to Run

1. **Compile the code** using a C++ compiler:
   ```bash
   g++ -o countryAnalyzer main.cpp
2. **Run the Code**

And BOOMmmm.
