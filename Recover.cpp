// Recover.cpp : Program to recover deleted JPGs from memory card
//
#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>

int main()
{   
    //Open files
    std::ifstream myfile("card.raw", std::ios::binary);
    std::ofstream mypic;
    int picnumber = 0;


    if (myfile.is_open())
    {
        std::cout << "File is ready to use\n";
    }

    // Copy all data from file into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(myfile), {});
    
    if (std::istreambuf_iterator<char>(myfile) == std::istreambuf_iterator<char>()) 
    {
        std::cout << "File sucessfully read\n";
        myfile.close();
    }
  
    //Search in buffer
    for (int index = 0; index < buffer.size(); index = index + 512)
    {
        //Find four right ordered bytes
        if (buffer[index] == 0xff && buffer[index + 1] == 0xd8 && buffer[index + 2] == 0xff && (buffer[index + 3] & 0xf0) == 0xe0)
        {            
            std::cout << "Values found\n";
          
            //Numerize files from 000-049
            std::string stringpic = std::to_string(picnumber);
            size_t n = 3;
            int precision = n - std::min(n, stringpic.size());
            std::string s = std::string(precision, '0').append(stringpic);
            
            mypic.open(s+".jpg",std::ios::binary);
           
            for (int it = index; it < buffer.size(); it++)
            {
                mypic << buffer[it];
                if (buffer[it] == 0xff && buffer[it + 1] == 0xd8 && buffer[it + 2] == 0xff && (buffer[it + 3] & 0xf0) == 0xe0&& it!=index)
                {
                    mypic.close();
                    picnumber++;
                    break;
                }
            }
        }
    }  
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
