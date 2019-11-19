#include <iostream>
#include <fstream> 
using namespace std;

int main()
{
	//header = new Header;
	ifstream fichier("uniprot_sprot.fasta.pin", ios::in | ios::binary);
	ifstream header("uniprot_sprot.fasta.phr", ios::in | ios::binary);
	if(fichier.is_open() && header.is_open())
	{
		int version = 0;
		int db_type;
		int title_length;
		char* title;
		char* title2;
		int timestampLength;
		char* timestamp;
		int nbSequences;
		int64_t residueCount;
		int maxSequence;
		
		fichier.read( (char*)(&version), sizeof(version) );
		version = __bswap_32(version); 
		//cout << version << endl;
		                                                    
		fichier.read( (char*)(&db_type), sizeof(db_type) );
		db_type = __bswap_32(db_type);	
		//cout << db_type << endl;
		
		fichier.read( (char*)(&title_length), sizeof(title_length) ); 
		title_length = __bswap_32(title_length);
		//cout << title_length << endl;
		
		title = new char[title_length]; 					
		fichier.read(title, title_length);
		//cout << title << endl;
		
		fichier.read( (char*)(&timestampLength), sizeof(timestampLength) );
		timestampLength = __bswap_32(timestampLength);
		//cout << timestampLength << endl;
		
		timestamp = new char[timestampLength];
		fichier.read(timestamp, timestampLength );
		//cout << timestamp << endl;
				
		fichier.read( (char*)(&nbSequences), sizeof(nbSequences) );
		nbSequences = __bswap_32(nbSequences);
		//cout << nbSequences << endl;
		
		fichier.read( (char*)(&residueCount), sizeof(residueCount) );
		//cout << (int)residueCount << endl;
		
		fichier.read( (char*)(&maxSequence), sizeof(maxSequence) );
		maxSequence = __bswap_32(maxSequence);
		//cout << maxSequence << endl;
		
		int headerOffsetTable[nbSequences+1]; 
		int sequenceOffsetTable[nbSequences+1];
		
		fichier.read( (char*)(&headerOffsetTable), sizeof(headerOffsetTable) );
		//cout << __bswap_32(headerOffsetTable[1]) << endl;
		//cout << __bswap_32(headerOffsetTable[2]) << endl;
		//cout << __bswap_32(headerOffsetTable[3]) << endl;
		
		fichier.read( (char*)(&sequenceOffsetTable), sizeof(sequenceOffsetTable) );
		
		
		for(int i=0; i < 100;i++)
		{
			header.seekg(__bswap_32(headerOffsetTable[i]));
			int8_t var;
			while(header.read( (char*)(&var), sizeof(var)))
			{
				//cout << hex << (unsigned int)(unsigned char) var << endl;
				if((unsigned int)(unsigned char) var == 160) //A0 en hex
				{
					int8_t var2;
					header.read( (char*)(&var2), sizeof(var2));
					//cout << hex << (unsigned int)(unsigned char) var2 << endl;
					if((unsigned int)(unsigned char) var2 == 128) //80
					{
						int8_t var3;
						header.read( (char*)(&var3), sizeof(var3));
						//cout << hex << (unsigned int)(unsigned char) var3 << endl;
						if((unsigned int)(unsigned char) var3 == 26) //1A
						{
							int8_t var4;
							header.read( (char*)(&var4), sizeof(var4));
							//cout << (unsigned int)(unsigned char) var4 << endl;
							if((unsigned int)(unsigned char) var4 > 128) 
							{
								int nbBytes = (unsigned int)(unsigned char)var4-128;
								//cout << nbBytes << endl;
								unsigned long int size;
								header.read((char*)(&size), nbBytes);
								cout << size << endl;
								//__bswap_32(size);
								//cout << (int)size << endl;
								title2 = new char[size];
								header.read(title2, size);
								cout << title2 << endl;
								delete(title2);
								break;
							}
							else {
								title2 = new char[var4];
								header.read(title2, var4);
								//cout << title2 << endl;
								delete(title2);
								break;
							}
						}
					}
				}
			}
		}
		delete(title);
	}
	fichier.close();
	header.close();
	return 0;
}


