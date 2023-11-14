// Copyright (c) 2018 by University Paris-Est Marne-la-Vallee
// Directory.cpp
// This file is part of the Garamon Generator.
// Authors: Stephane Breuils and Vincent Nozick
// Contact: vincent.nozick@u-pem.fr
//
// Licence MIT
// A a copy of the MIT License is given along with this program


#include "Directory.hpp"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/types.h> // required for stat.h
#include <sys/stat.h>
#include <regex>       // for substitute


#if defined(_WIN32) && defined(__MINGW32__)
	#include <direct.h>
	#include <io.h>
#endif // __WINDOWS Mingw compiler__

//Créer dossier avec nom spécifié par dirName
void makeDirectory(const std::string &dirName) {

    int nError = 0;

#if defined(_WIN32)
	nError = _mkdir(dirName.c_str()); // can be used on Windows
#else
    mode_t nMode = 0733; // UNIX style permissions
    nError = mkdir(dirName.c_str(), nMode); // can be used on non-Windows
#endif

    // handle your error here
    if (nError != 0) {
        std::cerr << "error: can not create directory: " << dirName << std::endl;
        exit(EXIT_FAILURE);
    }
}

//vérifie si dossier existe
bool directoryExists(const std::string &dirName) {

    struct stat info;//pour obtenir info sur fichier ou dossier

    if(stat( dirName.c_str(), &info ) != 0)
        return false; // cannot access to the directory

    if(info.st_mode & S_IFDIR) // in case of problem, check with: S_ISDIR()
        return true;

    return false;  // file exists but is not a directory
}

//vérifie si dossier ou fichier existe
bool directoryOrFileExists(const std::string &dirName) {

    struct stat info;

    if(stat( dirName.c_str(), &info ) == 0)
        return true; // can access to the directory or file

    return false;
}

//utilise ifstream pour ouvrir fichier ou dossier spécifié (name)
bool directoryOrFileExists_ifstream (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

//lit contenu fichier spécifié (fileName)
std::string readFile(const std::string &fileName) {

    std::ifstream myfile;//ouvre myfile
    myfile.open(fileName, std::ios::in);//ouvre fichier mode lecture

    // check if the file is opened
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    // copy the data to a string
    std::string data;
    data.assign( (std::istreambuf_iterator<char>(myfile)) , (std::istreambuf_iterator<char>()) );

    myfile.close();

    return data;
}

//ouvre en mode écriture
bool writeFile(const std::string &data, const std::string &fileName) {

    std::ofstream myfile(fileName);
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << fileName << std::endl;
        return false;
    }

    myfile << data;//écrit la chaine de caractère donnée (data) dans le fichier
    myfile.close();//ferme le fichier

    return true;
}




//permet de subsituer la chaine de caractère "data"
//pattern = chaine de caractère qu'on recherche dans fichier data
//replaceby = chaine de caractère par laquelle on veut remplacer celle de pattern
void substitute(std::string &data, const std::string &pattern, const std::string &replaceBy) {

    data = std::regex_replace(data, std::regex(pattern), replaceBy);//remplace les 2 entre elles
}

//copie un fichier depuis l'emplacement initial vers la destination
bool copyBin(const std::string &src, const std::string &dest) {

    std::ifstream srcFile(src, std::ios::binary);
    std::ofstream destFile(dest, std::ios::binary);
    destFile << srcFile.rdbuf();

    return srcFile && destFile;
}

//copie fichier texte d'une source vers destination
bool copyText(const std::string &src, const std::string &dest) {

    std::ifstream srcFile(src);
    std::ofstream destFile(dest);
    destFile << srcFile.rdbuf();

    return srcFile && destFile;
}
