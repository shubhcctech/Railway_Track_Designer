# Railway_Track_Designer
This project is a railway track generator implemented in C++ using Qt for the GUI and OpenGL for rendering. It allows users to visualize and manipulate Bezier curves and B-Splines to generate railway tracks.

## File Structure

- **Bezier.cpp:** Implementation of the Bezier curve functionality.
- **BSpline.cpp:** Implementation of the B-Spline functionality.
- **Container.cpp:** Implementation of a container class to manage control points.
- **main.cpp:** Entry point of the application.
- **OpenGLWindow.cpp:** Implementation of the OpenGL rendering window.
- **Point3D.cpp:** Implementation of a 3D point class.
- **Visualizer.cpp:** Implementation of the GUI and user interaction.

## Control Flow

1. **main.cpp:** Entry point of the application. Creates a QApplication and shows the main window.
2. **Visualizer.cpp:** Sets up the GUI components including buttons, spin boxes, and OpenGL windows.
3. **OpenGLWindow.cpp:** Handles OpenGL rendering and user interaction events such as mouse movements and button clicks.
4. **Container.cpp:** Manages control points for Bezier curves and B-Splines.
5. **Bezier.cpp:** Implements Bezier curve functionality including drawing curves and control points.
6. **BSpline.cpp:** Implements B-Spline functionality including drawing curves and control points.
7. User interacts with the GUI to add control points, choose curve types, and visualize the generated railway tracks.

## Usage

1. Run the application.
2. Use the GUI to add control points and select curve types.
3. Click the "DISPLAY" button to visualize the generated railway tracks.


# Project Header Files Overview

This project consists of several header files, each serving a distinct purpose within the codebase. Below is an overview of each header file and its role in the project's control flow:

## Bezier.h

- **Header file**: `Bezier.h`
- **Namespace**: `Feature`
- **Class**: `Bezier`

### Description:
- This header file defines the `Bezier` class responsible for handling Bezier curves.
- It provides functionalities to draw Bezier curves based on control points.

## BSpline.h

- **Header file**: `BSpline.h`
- **Namespace**: `Feature`
- **Class**: `BSpline`

### Description:
- This header file declares the `BSpline` class for managing B-Spline curves.
- It includes functionalities to evaluate and draw B-Spline curves based on control points.

## Container.h

- **Header file**: `Container.h`
- **Namespace**: `DS`
- **Class**: `Container`

### Description:
- This header file defines the `Container` class responsible for managing data storage.
- It handles storage for control points, vertices, and colors used in the project.

## OpenGLWindow.h

- **Header file**: `OpenGLWindow.h`

### Description:
- This header file defines the `OpenGLWindow` class, which inherits from `QOpenGLWidget`.
- It provides functionalities for rendering OpenGL graphics and handling user interactions.
- It includes methods for displaying Bezier and B-Spline curves and managing OpenGL rendering.

## Point3D.h

- **Header file**: `Point3D.h`
- **Namespace**: `Geometry`
- **Class**: `Point3D`

### Description:
- This header file declares the `Point3D` class representing a 3D point in space.
- It includes methods for accessing and modifying the coordinates of the point.

## Visualizer.h

- **Header file**: `Visualizer.h`

### Description:
- This header file defines the `Visualizer` class, which inherits from `QMainWindow`.
- It handles the main visualization window and user interface functionalities.
- This class integrates with OpenGL rendering and provides user interaction controls.



