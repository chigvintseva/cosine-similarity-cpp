# C++ Cosine Similarity  Algorithm (Texts Comparison and OpenGl Visualization)

## Project Overview
This project implements a program that calculates the **Cosine Similarity** between two input texts and visualizes the result using OpenGL. The program filters text, tokenizes it, calculates the cosine similarity, and then displays the angle between the two vectors in a graphical window. It explains cosine similarity if the user requests it and demonstrates how similar two texts are by comparing their word frequencies (simple comparison, meaning the worth of words is not considered).

## Features
- **Cosine Similarity Calculation**: Computes similarity based on word frequencies from two input texts.
- **Text Filtering & Tokenization**: Texts are filtered to remove unwanted characters (e.g. punctuation) and to ignore the uppercase letters and are split into tokens by space " " for comparison.
- **Cosine Similarity Visualization**: Uses OpenGL to visually represent the angle between the text vectors in a circle, where:
- Cosine similarity value and angle in degrees are displayed in the window.
- The green portion represents the angle between vectors (more green = lower similarity).
- **Interactive Explanation**: The user can request a detailed explanation of the Cosine Similarity concept.

## How it Works
1. **Greeting & Concept Explanation**: the program greets the user, and defines Cosine Similarity if requested
2. **Text Input**: The program asks the user to input two texts.
3. **Cosine Similarity Calculation**:
   - Words are filtered and tokenized.
   - Vectors representing word frequencies are built.
   - The **Cosine Similarity** is calculated based on the vectors.
   - The result is output as both a similarity score and an angle in degrees.
4. **Visualization**: The result is graphically visualized using OpenGL in a separate window, showing the angle between the vectors.

## Getting Started
### Prerequisites
- C++ compiler
- OpenGL and GLUT libraries installed

## License
This project is part of a university assignment for the Computer Science for Digital Engineering (with C++ and CAD) course.


