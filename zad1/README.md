1.(4pkt) Zaimplementuj struktury danych oraz procedury pozwalajace na przechowanie grafu w postaci macierzy sasiedztwa i (mozliwosc wczytania z pliku - pierwszy wiersz rozmiar macierzy, w kazdej lini inna binarna liczba):

	

a)dodanie \ usuniecie, krawedzi \ wierzcholka (zmiana z 1 na 0 lub odwrotnie)
	
b)wypisanie stopnia wierzcholka, stopnia minimalnego i max grafu,
	
c)wypisanie, ile jest wirzcholkow stopnia parzystego i nieparzystego
	
d)wypisanie (posortowanego nierosnaco) ciagu stopni



2.(2pkt) W oparciu o macierzowa reprezentacje grafu postaci macierzy sasiedztwa zaimplementuj procedure ktora sprawdza czy w grafie jest cykl C3 (czy graf zawiera podgraf izomorficzny z C3):
	

a) metoda naiwna
	
b) metoda oparta na mnozeniu macierzy

	cykl 3 - graf trojkat (czy graf zawiera trojkat)

	

ad 1) metoda naiwna - czy istnieja i,j,k (i != j != k) takie ze {i,j} e E, {j,k} e E
, {i,k} e E
	
ad 2) mnozenie dwoch taki samych macierzy przez siebie , wynikiem jest ilosc sciezek po przejsciu 2 krawedzi do danego punktu. Ostatecznie szukamy w pierwszej macierzy 1 a w wymnożonej 3.



3.(3pkt) Zaimplementuj procedure sprawdzajaca, czy dany ciag jest graficzny. Jesli jest, procedura powinna zwrocic przyklad takiego grafu realizujacego ten ciag.

	

3.1 Pierwzy etap (1pkt)
		
Przyklad:
		
		
		a) 43151355  
			
			1) suma wyrazow/stopni (tutaj 27) powinna byc parzysta, jak nie jest to nie ma grafu
		
		
		b) 54226322
			
			1) suma wyrazow/stopni (tutaj 26) parzysta
			
			2) sortujemy liczby
			  
				bierzemy tyle liczb ile pierwsza, tutaj 6 liczb po "szostce"
 i odejmujemy od nich 1 i 				dopisujemy pozostale
 5-1,4-1,3-1,2-1,2-1,2-1,2
			
			3) sortujemy ponownie i powtarzamy algorytm
 3-1,2-1,1-1,1-1,1
 >> 2,1,1,0,0 - po posortowaniu
					4) musza byc na koncu same zera zeby byl graficzny np. (3,2,1,0) nie zadziala mimo ze parzysty // 				przyklad do sprawdzenia
 odpowiedz NIE.
	
	

3.2 Przyklad grafu (2pkt) - moj pomysl zeby robic podczas sprawdzania czy ciag jest graficzny.



Za dwa tygodnie.
				
