#include <NIELIT_ESP32_Practicals.h>

/*
 * ============================================================
 * NIELIT ROPAR
 * Practical 2.12
 *co
 * Embedded Machine Learning
 * Inline Iris Data Flower Classification
 *
 * Platform : ESP32
 * Dataset  : Iris Dataset
 * Model    : Pre-Trained Decision Tree
 *
 * The classification is performed completely on the ESP32.
 *
 * No WiFi
 * No Cloud API
 * No MQTT
 * ============================================================
 */


// ------------------------------------------------------------
// IRIS CLASS DEFINITIONS
// ------------------------------------------------------------

enum IrisClass {
  IRIS_SETOSA = 0,
  IRIS_VERSICOLOR = 1,
  IRIS_VIRGINICA = 2
};


// ------------------------------------------------------------
// PRE-TRAINED EMBEDDED MACHINE LEARNING MODEL
// ------------------------------------------------------------
//
// Input Features:
// 1. Sepal Length
// 2. Sepal Width
// 3. Petal Length
// 4. Petal Width
//
// The following decision rules represent a compact
// pre-trained Decision Tree for Iris classification.
//
// ------------------------------------------------------------

IrisClass predictIris(
  float sepalLength,
  float sepalWidth,
  float petalLength,
  float petalWidth
) {

  // ----------------------------------------------------------
  // NODE 1
  // Setosa is easily separated using petal width.
  // ----------------------------------------------------------

  if (petalWidth <= 0.80) {

    return IRIS_SETOSA;

  }


  // ----------------------------------------------------------
  // NODE 2
  // Separate Versicolor and Virginica.
  // ----------------------------------------------------------

  if (petalWidth <= 1.75) {


    // --------------------------------------------------------
    // NODE 3
    // --------------------------------------------------------

    if (petalLength <= 4.95) {

      return IRIS_VERSICOLOR;

    }


    // --------------------------------------------------------
    // NODE 4
    // --------------------------------------------------------

    else {

      if (petalWidth <= 1.55) {

        return IRIS_VIRGINICA;

      }

      else {

        return IRIS_VERSICOLOR;

      }

    }

  }


  // ----------------------------------------------------------
  // VIRGINICA REGION
  // ----------------------------------------------------------

  else {


    // --------------------------------------------------------
    // NODE 5
    // --------------------------------------------------------

    if (petalLength <= 4.85) {


      // ------------------------------------------------------
      // NODE 6
      // ------------------------------------------------------

      if (sepalLength <= 5.95) {

        return IRIS_VERSICOLOR;

      }

      else {

        return IRIS_VIRGINICA;

      }

    }


    return IRIS_VIRGINICA;

  }

}


// ------------------------------------------------------------
// CONVERT CLASS NUMBER INTO FLOWER NAME
// ------------------------------------------------------------

const char* getClassName(IrisClass irisClass) {

  switch (irisClass) {

    case IRIS_SETOSA:

      return "Iris Setosa";


    case IRIS_VERSICOLOR:

      return "Iris Versicolor";


    case IRIS_VIRGINICA:

      return "Iris Virginica";


    default:

      return "Unknown";

  }

}


// ------------------------------------------------------------
// DISPLAY INPUT INSTRUCTIONS
// ------------------------------------------------------------

void showInstructions() {

  Serial.println();

  Serial.println(
    "================================================"
  );

  Serial.println(
    "Enter four Iris flower measurements:"
  );

  Serial.println();

  Serial.println(
    "SepalLength SepalWidth PetalLength PetalWidth"
  );

  Serial.println();

  Serial.println(
    "Example:"
  );

  Serial.println(
    "5.1 3.5 1.4 0.2"
  );

  Serial.println(
    "================================================"
  );

  Serial.println();

  Serial.print(
    "Enter Measurements > "
  );

}


// ------------------------------------------------------------
// SETUP
// ------------------------------------------------------------

void setup() {

  Serial.begin(115200);


  delay(1000);


  Serial.println();

  Serial.println(
    "================================================"
  );

  Serial.println(
    "       NIELIT ROPAR - Practical 2.12"
  );

  Serial.println(
    "       Embedded Machine Learning"
  );

  Serial.println(
    "       Iris Flower Classification"
  );

  Serial.println(
    "================================================"
  );


  Serial.println();

  Serial.println(
    "ML Model        : Pre-Trained Decision Tree"
  );

  Serial.println(
    "Dataset         : Iris Dataset"
  );

  Serial.println(
    "Inference Mode  : Local Edge Inference"
  );

  Serial.println(
    "Internet        : Not Required"
  );

  Serial.println(
    "Cloud API       : Not Required"
  );

  Serial.println();

  Serial.println(
    "Embedded ML Model Ready!"
  );


  showInstructions();

}


// ------------------------------------------------------------
// MAIN LOOP
// ------------------------------------------------------------

void loop() {


  // ----------------------------------------------------------
  // CHECK FOR SERIAL INPUT
  // ----------------------------------------------------------

  if (Serial.available() > 0) {


    /*
     * Read one complete line entered by the student.
     *
     * Example:
     *
     * 5.1 3.5 1.4 0.2
     */

    String input =
      Serial.readStringUntil('\n');


    input.trim();


    // Ignore empty input

    if (input.length() == 0) {

      return;

    }


    // --------------------------------------------------------
    // FEATURE VARIABLES
    // --------------------------------------------------------

    float sepalLength;
    float sepalWidth;
    float petalLength;
    float petalWidth;


    // --------------------------------------------------------
    // PARSE SERIAL INPUT
    // --------------------------------------------------------

    int valuesRead =
      sscanf(
        input.c_str(),
        "%f %f %f %f",
        &sepalLength,
        &sepalWidth,
        &petalLength,
        &petalWidth
      );


    // --------------------------------------------------------
    // VALIDATE NUMBER OF FEATURES
    // --------------------------------------------------------

    if (valuesRead != 4) {

      Serial.println();

      Serial.println(
        "ERROR: Please enter exactly four measurements."
      );


      Serial.println();

      Serial.println(
        "Correct Format:"
      );

      Serial.println(
        "SepalLength SepalWidth PetalLength PetalWidth"
      );


      Serial.println();

      Serial.println(
        "Example:"
      );

      Serial.println(
        "5.1 3.5 1.4 0.2"
      );


      showInstructions();


      return;

    }


    // --------------------------------------------------------
    // VALIDATE FEATURE VALUES
    // --------------------------------------------------------

    if (
      sepalLength <= 0 ||
      sepalWidth <= 0 ||
      petalLength <= 0 ||
      petalWidth <= 0
    ) {

      Serial.println();

      Serial.println(
        "ERROR: All measurements must be greater than zero."
      );


      showInstructions();


      return;

    }


    // --------------------------------------------------------
    // DISPLAY INPUT FEATURE VECTOR
    // --------------------------------------------------------

    Serial.println();

    Serial.println();

    Serial.println(
      "------------------------------------------------"
    );

    Serial.println(
      "INPUT FEATURE VECTOR"
    );

    Serial.println(
      "------------------------------------------------"
    );


    Serial.print(
      "Sepal Length : "
    );

    Serial.print(
      sepalLength,
      2
    );

    Serial.println(
      " cm"
    );


    Serial.print(
      "Sepal Width  : "
    );

    Serial.print(
      sepalWidth,
      2
    );

    Serial.println(
      " cm"
    );


    Serial.print(
      "Petal Length : "
    );

    Serial.print(
      petalLength,
      2
    );

    Serial.println(
      " cm"
    );


    Serial.print(
      "Petal Width  : "
    );

    Serial.print(
      petalWidth,
      2
    );

    Serial.println(
      " cm"
    );


    // --------------------------------------------------------
    // START INFERENCE TIMER
    // --------------------------------------------------------

    unsigned long inferenceStart =
      micros();


    // --------------------------------------------------------
    // RUN EMBEDDED ML INFERENCE
    // --------------------------------------------------------

    IrisClass prediction =
      predictIris(
        sepalLength,
        sepalWidth,
        petalLength,
        petalWidth
      );


    // --------------------------------------------------------
    // STOP INFERENCE TIMER
    // --------------------------------------------------------

    unsigned long inferenceEnd =
      micros();


    unsigned long inferenceTime =
      inferenceEnd -
      inferenceStart;


    // --------------------------------------------------------
    // DISPLAY ML RESULT
    // --------------------------------------------------------

    Serial.println();

    Serial.println(
      "------------------------------------------------"
    );

    Serial.println(
      "MACHINE LEARNING INFERENCE RESULT"
    );

    Serial.println(
      "------------------------------------------------"
    );


    Serial.print(
      "Predicted Class : "
    );


    Serial.println(
      getClassName(
        prediction
      )
    );


    Serial.print(
      "Class ID        : "
    );


    Serial.println(
      (int)prediction
    );


    Serial.print(
      "Inference Time  : "
    );


    Serial.print(
      inferenceTime
    );


    Serial.println(
      " microseconds"
    );


    Serial.println(
      "Execution       : ESP32 Local Edge"
    );


    Serial.println(
      "Cloud API       : NONE"
    );


    Serial.println(
      "------------------------------------------------"
    );


    // --------------------------------------------------------
    // READY FOR NEXT SAMPLE
    // --------------------------------------------------------

    showInstructions();

  }

}