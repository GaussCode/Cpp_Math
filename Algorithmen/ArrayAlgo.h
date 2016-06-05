/*
  ArrayAlgo.h
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-06-05
  Version: 1
  
  Beschreibung: Enthält Algorithmen, die die Variationen und
                Kombinationen von eindimensionalen Arrays berechnen.
                Da die Funktionen template-Funktionen sind, werden sie
                direkt in dieser Datei vollständig beschrieben.
  
  (c) Alle Rechte vorbehalten.
*/


#include <iostream>


namespace VMath {



/*
  PRINT: 
    Hilfsfunktion, um einen Array auszuschreiben.
    Es wird kein Trennzeichen verwendet.
*/
template<typename T>
void print(T* a, int len, int tabs = 0) {
  for (int i = 0; i < tabs; i++) {
    std::cout << " ";
  }
  
  for (int i = 0; i < len; i++) {
    std::cout << a[i];
  }
  
  std::cout << std::endl;
}



/*
  PERMUTATE: 
    Berechnet alle Permutationen des Eingabevektors bis zu maximal max_iter.
    Parameter:
      @input:     Eingabevektor eines beliebigen Typs
      @len:       Länge des Eingabevektors
      @max_iter:  Anzahl der zu berechnenden Iterationen. Wenn diese
                  Anzahl über len! liegt, wird nur bis len! ausgerechnet.
                  Falls max_iter < 0 ist, wird bis len! ausgerechnet.
      @writeOut:  Gibt an, ob jede Zwischenpermutation ausgeschrieben
                  werden soll.
      @rest:      Nur wichtig für die Rekursion und sollte nicht angegeben
                  werden. Standardmäßig auf nullptr gesetzt. (s.u.)
      @offset:    Auch nur für die Rekursion. Für Erklärung siehe unten.
    Return:
      Verändertes max_iter. Siehe dafür das Beispiel unten. Nur wichtig
      für die Rekursion. Man könnte stattdessen auch einen Pointer und
      stattdessen keinen Rückgabewert verwenden, das würde jedoch den 
      Komfort für den Benutzer einschränken.
  
  Algorithmus-Skizze für len = 3:  
  [123] -> 1[23] -> 2[3] => input = [123], max_iter = 6
                 -> 3[2] => input = [132], max_iter = 5
        -> 2[31] -> 3[1] => input = [231], max_iter = 4
                 -> 1[3] => input = [213], max_iter = 3
        -> 3[12] -> 1[2] => input = [312], max_iter = 2
                 -> 2[1] => input = [321], max_iter = 1
  
  Dabei wird der Array, der immer die n-1 letzten Zahlen umfasst,
  in der Funktion als "rest" bezeichnet. Der Beginnindex des Arrays
  im Orignal-Array wird dann als "offset" bezeichnet.
*/
template<typename T>
int permutate(T* input, int len, int max_iter, bool writeOut = false,
                T* rest = nullptr, int offset = 0) {
                
  if (max_iter == 0) return 0;
  if (offset == len) {
    if (writeOut) print(input, len);
    return max_iter-1;
  }
  
  // Beim ersten Aufruf
  if (rest == nullptr) {
    rest = new T[len];
    for (int i = 0; i < len; i++)
      rest[i] = input[i];
  }
   
  int rest_len = len - offset;  
  for (int i = 0; i < rest_len; i++) {
    input[offset] = rest[i];    
    
    // Hier wird der rest-Array für die Unterebene angelegt
    T* rest_tmp = new T[rest_len-1];    
    for (int j = 1; j < rest_len; j++) {
      rest_tmp[j-1] = rest[(i+j) % (rest_len)];
    }
    
    max_iter = permutation(input, len, max_iter, writeOut, rest_tmp, offset+1);    
    if (max_iter == 0) return 0;
  }
  
  return max_iter;
}



/*
  COMBINATIONS:
    Berechnet alle in der Grundmenge / dem Alphabet möglichen Kombinationen
    mit der Länge combi_len.
    Parameter:
      @alphabet:  Die Grundmenge aus der die Wörter / Kombinationen gebildet 
                  werden.
      @len:       Länge von @alphabet.
      @combi_len: Länge der zu berechnenden Kombinationen
      @writeOut:  Gibt an, ob die Zwischenkombinationen auch ausgegeben werden
                  sollen.        
*/
template<typename T>
void combinations(T* alphabet, int len, int combi_len, int max_iter,
                  bool writeOut = false) {
  
}
       
};

