// wave.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "iostream"
using namespace std;

// Only valid for 16 bit wave files!
// 11k16bitpcm.wav
#define PATH "F:\\code\\wave\\files\\11k16bitpcm.wav"
#define DEST "F:\\code\\wave\\files\\out.wav"


// Class Definition 

class wav
	{
	// metadata  
	char ChunkID[5], Format[5], Subchunk1ID[5],Subchunk2ID[5];
	int ChunkSize,Subchunk1Size, SampleRate, ByteRate,Subchunk2Size,test;
	short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
	unsigned short *Data;

	

	// Read wave file
	public :
	wav(char[100]); // class contructor - arg filepath 
	void wavread(FILE *fhandle);
	void wavwrite(FILE * fhandle);
	};


// constructor definition 
wav::wav(char path[100])
{
	FILE *fhandle=fopen(PATH,"rb"); // Currently using def to pass PATH as predefined value - Need to find a way to pass argument
	ChunkID[4] = Format[4] = Subchunk1ID[4] = Subchunk2ID[4] = '\0';
	wavread(fhandle); //call wavread
	fclose(fhandle);

	fhandle=fopen(DEST,"wb");
	wavwrite(fhandle); // call wavwrite
	fclose(fhandle);
}




// def wavread 
void  wav::wavread(FILE * fhandle)
{
	FILE* fp = fopen("Data-read.txt", "w");
	fread(ChunkID,1,4,fhandle);
	fread(&ChunkSize,4,1,fhandle);
	fread(Format,1,4,fhandle);
	fread(Subchunk1ID,1,4,fhandle);
	fread(&Subchunk1Size,4,1,fhandle);
	fread(&AudioFormat,2,1,fhandle);
	fread(&NumChannels,2,1,fhandle);
	fread(&SampleRate,4,1,fhandle);
	fread(&ByteRate,4,1,fhandle);
	fread(&BlockAlign,2,1,fhandle);
	fread(&BitsPerSample,2,1,fhandle);
	fread(&Subchunk2ID,1,4,fhandle);
	fread(&Subchunk2Size,4,1,fhandle);
	Data=new unsigned short [Subchunk2Size/(BitsPerSample/8)]; // Create an element for every sample
	fread(Data,BitsPerSample/8,Subchunk2Size/(BitsPerSample/8),fhandle); // Reading raw audio data
	
	for (int i=0; i < Subchunk2Size/(BitsPerSample/8); i++)
	{
		fprintf(fp, "%d \n", Data[i]);
	}

	std::cout << "In wavwrite \n data[3]" << Data[3] << " ChunkID " 
		      << ChunkID << " ChunkSize " << ChunkSize << " BitsPerSample "
			  << BitsPerSample << " SubChunkSize " <<Subchunk2Size;
	//return *Data;
	fclose(fp);
}


void wav::wavwrite(FILE * fhandle)
{		
	FILE* fp = fopen("Data-written.txt", "w");
	std::cout << "In wavwrite \n data[3]" << Data[3] << " ChunkID " 
		      << ChunkID << " ChunkSize " << ChunkSize << " BitsPerSample "
			  << BitsPerSample << " SubChunkSize " <<Subchunk2Size;
	fwrite(ChunkID,1,4,fhandle);
	fwrite(&ChunkSize,4,1,fhandle);
	fwrite(Format,1,4,fhandle);
	fwrite(Subchunk1ID,1,4,fhandle);
	fwrite(&Subchunk1Size,4,1,fhandle);
	fwrite(&AudioFormat,2,1,fhandle);
	fwrite(&NumChannels,2,1,fhandle);
	fwrite(&SampleRate,4,1,fhandle);
	fwrite(&ByteRate,4,1,fhandle);
	fwrite(&BlockAlign,2,1,fhandle);
	fwrite(&BitsPerSample,2,1,fhandle);
	fwrite(&Subchunk2ID,1,4,fhandle);
	fwrite(&Subchunk2Size,4,1,fhandle);
	fwrite(Data,BitsPerSample/8,Subchunk2Size/(BitsPerSample/8),fhandle);  //****
	for (int i=0; i < Subchunk2Size/(BitsPerSample/8); i++)
	{
		fprintf(fp, "%d \n", Data[i]);
	}
	fclose(fp);
	
}	
/// ****wav::Data is not being passed appropriately - Everything else seems to be writing just fine to out.wav






// ---------------- main -------------------- //

void main()
{
 wav wave1("F:\\code\\wave\\files\\11k16bitpcm.wav");
 cin.get();
}

