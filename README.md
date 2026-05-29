# ANAC Air Network System

ANAC Air Network System is a C console application for managing a small airline network.
It allows you to register airports, register flights between airports, remove flights,
list active flights, and search for possible routes in the network.

## Purpose

This project simulates a simplified airline route manager:

- Register airports in the network
- Register flights using flight IDs
- Remove flights by ID
- Display all registered flights
- Search possible routes between airports

The application uses a graph structure to represent the airport network and a sparse matrix
backing structure to store flight edges efficiently.

## How it works

The program is organized around two core data structures:

- **Graph**: stores airports as vertices and flights as edges.
- **Sparse matrix**: stores flight relationships compactly instead of using a dense matrix.

### Main features

1. **Airport registration**
   - Adds an airport to the network.

2. **Flight registration**
   - Adds a flight between two registered airports.
   - Each flight has a unique numeric ID.

3. **Flight removal**
   - Removes a flight using its ID.

4. **Flight listing**
   - Shows all registered flights grouped by departure airport.

5. **Route search**
   - Searches reachable paths between two airports and prints the route.

## Running the program

### Compile

From the project root, compile all C sources with GCC:

```bash
gcc main.c graph/graph.c sparse-matrix/sparse_matrix.c -o anac-system
```

### Execute

On Linux/macOS:

```bash
./anac-system
```

On Windows (PowerShell):

```powershell
./anac-system.exe
```

## Console menu

When the program starts, you will see a menu with these options:

1. Register new airport
2. Register flight
3. Remove flight
4. List flights
5. List possible routes
6. Exit program

### Example workflow

1. Register one or more airports.
2. Register flights between them using unique IDs.
3. View the list of flights.
4. Search routes between airports.
5. Exit the program.

## Requirements

- GCC or another C compiler
- A terminal or command prompt

## Notes

The project is intentionally small and educational. It demonstrates how graph structures can be
combined with sparse storage to model real-world network relationships.
