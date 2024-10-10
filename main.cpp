// import necessary libraries
#include <iostream>
#include <unordered_map>
#include <set>
#include <GL/glut.h> // library for visualization
#include <string>
#include <vector>
#include <sstream> // for tokenization in tokenizeBySpace() function
#include <cmath> // for sqrt() in CosineSimilarity() function and visualization
using namespace std;

//  declare global variables
double cosineSimilarityValue; // variable to store cosine similarity value
double angleInDegrees; // variable to store the angle in degrees

// function to explain cosine similarity if asked by user
void cosSimExplain() {
    string answerExplain; // variable to store user's answer

    cout << "Do you want to know what the Cosine Similarity is?\nAnswer with 'yes' or 'no': ";
    getline(cin, answerExplain); // getting the input

    if (answerExplain == "yes") {
        // explain the concept
        cout << "Cosine Similarity is a metric used to measure similarity in the direction or orientation of vectors\n";
        cout << "ignoring differences in their magnitude or scale by calculating the angle between them: \n";
        cout << "smaller angles indicate higher similarity.\nThis algorithm filters text, counts word frequencies, \n";
        cout << "and outputs a similarity score (from 0 to 1), and the angle in degrees, \n";
        cout << "where 0 degrees means identical texts and 90 degrees means completely different.\n";
        cout << "In simple words, it measures how similar two texts are by comparing the words they contain.\n";
        cout << "Now let's jump to the work!\n";
    } else if (answerExplain == "no") {
        // skip explanation
        cout << "Let's jump to the work!\n";
    } else {
        // if input is invalid, explain the answer requirement
        cout << "Sorry, couldn't understand you.\nCheck whether the answer is written with lower case latin characters only, please.\nLet's try again: ";
        // run this function again
        cosSimExplain();
    }
}

// function to filter a text to ignore other symbols apart from letters, numbers,
// and spaces and to keep all letter in lower case
string filterText (const string& text) {
    string filteredText; // declare string to store filtered text

    // loop through every symbol in text
    for (char nowSym : text) {
        // check whether current symbol is letter or space
        if (isalpha(nowSym) || isspace(nowSym) || isdigit(nowSym)) {
            // add the current symbol to the filtered text if it has letter, digit or space IN LOWER CASE
            filteredText += tolower(nowSym);
        }
    }
    return filteredText;
    }

//function to tokenize a text using stringstream
vector <string> tokenizeBySpace(const string& text) {
    vector <string> tokenizedText; // declare vectore to store tokens
    string token; // to store the current token
    stringstream ss(text); //created strngstream for text tokenization

    // while loop for tokenizing the string by spaces
    while (ss >> token) {
        tokenizedText.push_back(token); // adding current token to vector
    }

    return tokenizedText;
}

// function to print the text withing window, to avoid extra duplication
void printInWindow(const string& text){
     for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    } // print every letter from any texts
}


// function to display visually the cosine similarity between two texts
void displayCircle() {
    glClear(GL_COLOR_BUFFER_BIT);

    int num_segments = 100;
    double radius = 0.5f;
    double angle_step = 2 * M_PI / num_segments;


    double portion = angleInDegrees / 360.0; // Calculate proportion of circle based on angle (0 to 360 degrees)


    // Draw the green portion representing the angle between vectors
    glColor3f(0.0, 1.0, 0.0); // Set color to green for the angle portion
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0.0, 0.0);  // Center of the circle
        // Loop through segments to fill based on the angle
        for (int i = 0; i <= num_segments * portion; i++) { // green section based on angle
            float angle = i * angle_step;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex3f(x, y, 0.0);
        }
    glEnd();

    // Draw the remaining portion of the circle in red (remaining angle)
    glColor3f(1.0, 0.0, 0.0); // Set color to red for the remaining part
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 0.0, 0.0);  // Center of the circle
        // Loop through remaining segments to complete the circle
        for (int i = num_segments * portion; i <= num_segments; i++) { // Fill remaining with red
            float angle = i * angle_step;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex3f(x, y, 0.0);
        }
    glEnd();

    // display the cosine similarity value inside the circle
    string similarityText = "Cosine Similarity: " + to_string(cosineSimilarityValue);
    glColor3f(0.0, 0.0, 0.0); // Set color to black for all texts
    glRasterPos2f(-0.35f, -0.1f); // position the similarityText at the center of the circle
    printInWindow(similarityText);

    // display other results and annotation without \n
    string angleText = "Angle between given texts (as vectors): " + to_string(angleInDegrees) + " degrees.";
    glRasterPos2f(-0.9f, -0.6f); // position below the circle
    printInWindow(angleText);

    string annotation = "Green color on the circle represents the angle between vectors.";
    glRasterPos2f(-0.9f, -0.7f);  // position below angleText
    printInWindow(annotation);

    string annotation2 = "E.g. the smaller the green sector, the higher the Cosine Similarity.";
    glRasterPos2f(-0.9f, -0.8f);  // position below annotation
    printInWindow(annotation2);

    glFlush();
}

// function to initialize and run OpenGl
int initOpenGL(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cosine Similarity Circle");
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Set background color to white

    glutDisplayFunc(displayCircle);
    glutMainLoop();
    return 0;
}

// function to find cosine similarity between two given texts
void calculateCosineSimilarity() {
    string text1, text2; // declare variables to store the given texts

    cout << "Please enter the first text: ";
    getline(cin, text1); // get the first text from user
    cout << "Please enter the second text: ";
    getline(cin, text2); // get the second text from user

    // declare variables for filtered text1 and tex2
    // assign it the return from the called function filterText
    string filteredText1 = filterText(text1);
    string filteredText2 = filterText(text2);

    // declare vectors for tokens from text1 and tex2
    // assign it the return from the called function tokenizeBySpace
    vector <string> tokensText1 = tokenizeBySpace(filteredText1);
    vector <string> tokensText2 = tokenizeBySpace(filteredText2);

    // declare set to add unique words only
    set <string> uniqueWords;

    // add all unique words from tokensText1 to the set
    for (const auto& word : tokensText1) {
        uniqueWords.insert(word);
    }
    // add all unique words from tokensText2 to the set
    for (const auto& word : tokensText2) {
        uniqueWords.insert(word);
    }

    // turn set into vector Vocabulary for further calculation
    vector <string> vocabulary (uniqueWords.begin(), uniqueWords.end());

    // create map of indexes for words in Vocabulary
    unordered_map <string, int> wordIndex;
    // add index for every word into map
    for (size_t i = 0; i< vocabulary.size(); ++i) {
        wordIndex[vocabulary[i]] = i;
    }

    // create vectors for texts with count of words from unique words Vocabulary
    vector<int> vec1(vocabulary.size(), 0);
    vector<int> vec2(vocabulary.size(), 0);

    // add counts in vec1 for text1
    for (const auto& word : tokensText1) {
        vec1[wordIndex[word]]++;  // incresing the count for every word from text1
    }

    // add counts in vec2 for text2
    for (const auto& word : tokensText2) {
        vec2[wordIndex[word]]++;  // increasing the count for every word from text2
    }

    // declare variable for dot product of vectors
    int dotProduct = 0;
    // declare variables to store the lengths of vectors
    double normA = 0;
    double normB = 0;

    // find dot product and norms of both vectors with word appearance count form texts
    for (size_t i=0; i < vec1.size(); ++i) {
        dotProduct +=vec1[i] * vec2[i];
        normA += vec1[i] * vec1[i];
        normB += vec2[i] * vec2[i];
    }

    // check whether one of vectors is 0, find cosine sim as cos of an angle
    if (normA == 0 || normB == 0) {
        cosineSimilarityValue = 0; // cos sim is always 0 for empty vector
    } else {
        cosineSimilarityValue = dotProduct / (sqrt(normA) * sqrt(normB));
    }

    // ensure that cosine similarity is within [-1,1] to avoid errors
    cosineSimilarityValue = max(-1.0, min(1.0, cosineSimilarityValue));

    // find angle in degrees
    angleInDegrees = acos(cosineSimilarityValue) * (180.0 / M_PI);
    // print outputs
cout << "Cosine Similarity between given texts: " << cosineSimilarityValue << ".\n";
cout << "Note: Due to the vector construction using word counts, the cosine similarity ranges from 0 to 1.\n";
cout << "This means that the angle calculated will be between 0° (identical texts) and 90° (completely different).\n";
cout << "Negative cosine similarity and angles approaching 180° are not possible with the current implementation.\n";
cout << "You can view the results and angle visualization within a circle inside another window.\n";
cout << "Restart the program to calculate the Cosine Similarity between other texts.\nHave a nice day!\n";
}

// main function to execute the program and ask whether to run again
int main(int argc, char** argv) {
    cout << "Hi! I'm Alena's Program to find the Cosine Similarity between two given texts.\n";

    cosSimExplain(); // call function with explanation of the concept if asked
    calculateCosineSimilarity(); // call function to find cosine similarity
    initOpenGL(argc, argv); // init OpenGl to draw the result

    return 0;
}
