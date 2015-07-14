task main()
{
  TFileHandle   hFileHandle;              // will keep track of our file
  TFileIOResult nIOResult;                // will store our IO results
  string        sFileName = "test.txt";   // the name of our file
  int           nFileSize = 2;          // will store our file size

  byte CR = 0x13;   // define CR (carriage return)
  byte LF = 0x10;   // define LF (line feed)

  char        incommingChar;                          // this will store each char as we read back in from the file
  int      numbers[2];                  // this will store the final, fully-read strings (with new strings getting put into new indexes
  int         nLineCounter = 0;                       // this will let us know which line we are on when reading and writing (used as the index to 'incommingString[]')

  OpenRead(hFileHandle, nIOResult, sFileName, nFileSize);     // open our file 'sFileName' for reading

  for(int i = 0; i < nFileSize; i++)
  {
  	ReadByte(hFileHandle, nIOResult, incommingChar);            // read in a single byte
  	numbers[i] = incommingChar - '0'; //convert char to int
  }
  Close(hFileHandle, nIOResult);                              // close our file (DON'T FORGET THIS STEP!)

  for(int i = 0; i < 2; i++)
  {
    nxtDisplayString(i,"%d", numbers[i]);
  }

  while(true);  // infinite loop to keep our program running so that we can view the ROBOTC debugger variables
}
