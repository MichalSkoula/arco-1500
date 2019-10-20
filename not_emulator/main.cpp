
int main(int argc, char** argv)
{
	millis();   // initialize time when program started
	setup();
	while (true) {
		loop();
	}
	return 0;
}
