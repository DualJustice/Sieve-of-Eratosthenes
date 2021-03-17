void askCapAndCreateArray();

static int *primeArray;

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		delay(250);
	}

	pinMode(LED_BUILTIN, OUTPUT);
	askCapAndCreateArray();

	Serial.println(primeArray[0]);

	int arrayBuffet = primeArray[0];
	int index = 0;
	while(arrayBuffet != -1) {
		Serial.println(arrayBuffet);

		index += 1;
		arrayBuffet = primeArray[index];
	}
}

int inputLoop() {
	int userInput = 0;

	while (true) {
		if (Serial.available() > 0) {
			userInput = Serial.parseInt();
			Serial.println(userInput);
			break;
		}

		else {
			delay(100);
		}
	}

	return userInput;
}

int *arrayLoop(int sieveCap) {
	int *buildArray = new int[sieveCap - 1];
	int *boolArray = new int[sieveCap - 1];

	for (int i = 0; i < (sieveCap - 1); i += 1) {
		buildArray[i] = i + 2;
		boolArray[i] = 1;
	}

	for (int j = 0; j < (sieveCap - 1); j += 1) {
		int jIndex = buildArray[j];

		if (boolArray[j] == 1) {
			for (int k = 1; k < sieveCap; k += 1) {
				int testVal = jIndex * k + j;

				if (testVal <= sieveCap) {
					boolArray[testVal] = 0;
				} 
				
				else {
					break;
				}
			}
		}
	}
	int primeArraySize = 0;

	for (int m = 0; m < (sieveCap - 1); m += 1) {
		if (boolArray[m] == 1) {
			primeArraySize += 1;
		}
	}

	int *THEALMOSTFINALARRAY = new int[sieveCap];

	for (int n = 0; n < (sieveCap - 1); n += 1) {
		THEALMOSTFINALARRAY[n] = boolArray[n] * buildArray[n];
	}

	THEALMOSTFINALARRAY[sieveCap] = -1;

	return THEALMOSTFINALARRAY;
}

void askCapAndCreateArray() {
	Serial.println("Please input a positive integer >= 2.");

	int sieveCap = -1;

	while(true) {
		sieveCap = inputLoop();

		if (sieveCap < 2) {
			Serial.println("Please make sure your input is >2.");
		}

		else {
			primeArray = arrayLoop(sieveCap);
			break;
		}
	}
}

void loop() {
	//delay(1000);
	//Serial.print(primeArray);
	//Serial.println();
}