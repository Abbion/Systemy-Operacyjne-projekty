# Problem pięciu filozofów zadanie
Zadanie zsynchronizowania działań pięciu filozofów, którzy siedzą przy okrągłym stole i myślą. Co jakiś
czas głodnieją i muszą się najeść. Przed każdym filozofem stoi talerz, a między kolejnymi talerzami leży
jeden widelec. Na środku stołu stoi półmisek z rybami. Ryby należy jeść dwoma widelcami, więc filozof
aby mógł jeść musi mieć do dyspozycji dwa widelce. Podnosząc leżące przed nim widelce filozof
uniemożliwia jedzenie sąsiadom. Zakłada się, że filozof w skończonym czasie się naje i odłoży widelec.

Rozwiązanie problemu musi gwarantować spełnienie następujących warunków:

• Każdy z filozofów będzie w końcu mógł się najeść,

• Nie można wyróżniać żadnego z filozofów (algorytmy wszystkich pięciu filozofów dotyczące
podnoszenia i odkładania widelców muszą być takie same).

Zazwyczaj rozważa się 3 rozwiązania problemu pięciu filozofów:

• Rozwiązanie z możliwością blokady; zgłodniały filozof czeka aż jeden z jego widelców (np. lewy)
będzie wolny i podnosi go, a następnie czeka aż będzie wolny drugi widelec i także go podnosi.
Po najedzeniu się odkłada widelce na stół. Może zdarzyć się sytuacja kiedy każdy z filozofów
podniesie jeden ze swoich widelców i będzie czekał aż jego sąsiad skończy jeść i odłoży widelec.
Ponieważ każdy z filozofów będzie czekał na to samo zdarzenie pojawi się blokada.

• Rozwiązanie z możliwością zagłodzenia; zgłodniały filozof podnosi jednocześnie dwa widelce
wtedy, gdy tylko są wolne. Jeżeli jeden z filozofów będzie miał żarłocznych sąsiadów, którzy
głównie będą zajmować się jedzeniem, tak że w każdej chwili przynajmniej jeden z nich będzie
jadł, to taka sytuacja doprowadzi do zagłodzenia tego filozofa.

• Rozwiązanie poprawne; sami filozofowie nie są w stanie rozwiązać problemu jedzenia, jeżeli
żaden z nich nie ma być wyróżniony. Potrzebny jest zewnętrzny arbiter (lokaj) decydujący,
którzy filozofowie będą mieli pierwszeństwo w spornych przypadkach. Lokaj dba o to, aby w
każdej chwili co najwyżej czterech filozofów konkurowało o widelce podnosząc je sekwencyjnie
(jak w rozwiązaniu 1). Wtedy zawsze przynajmniej jeden z filozofów będzie mógł podnieść
widelec i jeść. Jeśli pięciu filozofów zapragnie jeść naraz, to lokaj powstrzyma jednego z nich
do czasu, aż któryś z pozostałych czterech skończy jeść.

Zaimplementować wszystkie trzy rozwiązania problemu pięciu filozofów używając semaforów.
Zademonstrować zjawiska blokady i zagłodzenia, jak też ich brak w rozwiązaniu poprawnym.
