# Pac-Man na parní pohon

## Autoři:
Tým parních mlátiček:
Vladimír Hucovič - xhucov00
Ondřej Zobal - xzobal01
Petr Kolouch - xkolou05

## Překlad
Spuštění `make` v kořenovém adresáři vytvoří složku build, ve které se nachází spustitelný soubor `parni-pacman`.
Spuštění `make run` kromě překladu také spustí hru.
`make doxygen` vygeneruje HTML dokumentaci programu v adresáři doc/html.

## Popis hry: 

Upravená hra stylu Pac-Man, kde má hráč za úkol posbírat všechny klíče na mapě a poté dorazit do cíle. Přitom se musí vyhýbat nepřátelským duchům. Hráč má 
na začátku hry k dispozici 2 životy. Pokud je zasažen duchem, ztrácí jeden život. Pokud ztratí všechny životy, hra končí. S malou šancí se v mapě může
na náhodném místě vyskytnout srdíčko, které hráči obnoví jeden život. Hráč však nikdy nepřekročí maximální počet životů, který je 3.

S malou šancí se v mapě také na náhodném místě může vyskytnout elixír, který hráči na malou chvíli umožní zneškodnit duchy při kontaktu.

Průběh hry se automaticky zaznamenává do souboru, který je pojmenovaný podle aktuálního času. V něm jsou zaznamenány pohyby hráče a duchů.
Tento záznam je pak možné si přehrát. 

Hra je rozšířena o režim dvou hráčů. Jeden z hráčů, který má roli serveru, vytvoří hru na specifikovaném portu a druhý hráč se k vytvořenému serveru připojí.

Soubor s mapou lze vybrat v hlavním menu. V případě hry dvou hráčů mapu vybírá hráč, který spouští server.

## Ovládání:

Klávesa W - pohyb nahoru
Klávesa S - pohyb dolů
Klávesa A - pohyb doleva
Klávesa D - pohyb doprava
Kliknutí levým tlačítkem myši na nějaké políčko - automatický pohyb hráče na toto políčko

## Ovládání záznamu:
Klávesa A - přepnutí mezi záznamem dopředu a dozadu
Klávesace Mezerník - Spuštění nebo pozastavení záznamu
Klávesa D - Pokud je záznam pozastaven, přehraje jeden snímek záznamu. V připadě podržení klávesy D se záznam přehrává dokud klávesa není uvolněna.

## Implementováno
- Hra pro jednoho hráče
- Hra pro dva hráče
- Ovládání myší
- Ovládání klávesnicí
- Zaznamenávání hry jednoho/dvou hráčů do souboru
- Přehrání záznamu po krocích nebo automaticky, pozastavení záznamu
- Interaktivní prvek - více životů a náhodné vyskytnutí srdíčka, které obnoví jeden život
- Interaktivní prvek - náhodné vyskytnutí elixíru - umožní hráči na krátkou dobu zneškodnit duchy
- Srdíčka i elixíry je možné také umístit přímo do mapy (B pro elixír, H pro srdíčko)

## Známé limitace
- Zpětné přehrávání záznamu nelze krokovat
- Záznam nelze přehrát od konce
- Při hraní přes ssh X11 je hra pomalá - pro lepší herní zážitek je nutno se připojit s přepínačem -C.





Pozn. aplikace a dokumentace zdrojového kódu jsou v anglickém jazyce
Autory grafických elementů jsou Vladimír Hucovič a Ondřej Zobal


