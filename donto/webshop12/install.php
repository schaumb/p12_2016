<?php

$DATABASE->exec("create database " . MYSQL_DATABASE_NAME);

$DATABASE->exec("CREATE TABLE IF NOT EXISTS `category` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `Description` text COLLATE utf8_unicode_ci,
  `Parent` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `Category_Id_uindex` (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;");

$categories = array(
    array(
        
    ),
);

$DATABASE->exec("CREATE TABLE IF NOT EXISTS `product` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `ProductId` int(11) DEFAULT NULL,
  `ProductName` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `Description` text COLLATE utf8_unicode_ci,
  `Price` int(11) DEFAULT NULL,
  `Image` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `product_Id_uindex` (`Id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=23 ;

--
-- A tábla adatainak kiíratása `product`
--

INSERT INTO `product` (`Id`, `ProductId`, `ProductName`, `Description`, `Price`, `Image`) VALUES
(1, 12345432, 'MiniCRM KickStart tanácsadás', '', 1000, 'minicrm.png'),
(2, 2147483647, 'Acer Aspire ONE Happy Citrom W7', 'leiras', 50800, 'UM11-06-0044n[1].jpg'),
(3, 6600000, 'Tucano Egér MMKER-U-NY kék/piros Urban/New York', 'A NetScroll 310X egér tökéletes mása a bevezető szIntű \"nagytestvér\" a NetScroll 100X egérnek. Ahogy a fotón is látszik a NetScroll 310X kis mérettel és súllyal rendelkezik.', 6350, 'UM11-02-0115n.jpg'),
(4, 6600001, 'Kensington ValuCase One', 'Belső táskaméret: 40 x 28,5 x 5,5 cm', 6756, 'UM07-05-0080n.jpg'),
(5, 6600002, 'Laptop táska HP Value Case (RR314AA)', 'Max. 15,4\" kijelzőjű laptophoz', 6629, 'UM10-06-0250n.jpg'),
(6, 6600003, 'Egér Genius Netscroll 310', 'A NetScroll 310X egér tökéletes mása a bevezető szIntű \"nagytestvér\" a NetScroll 100X egérnek. Ahogy a fotón is látszik a NetScroll 310X kis mérettel és súllyal rendelkezik.', 4318, 'UM09-04-0098n.jpg'),
(7, 6600004, 'Egér USB optical Blue Spyker', 'A NetScroll 310X egér tökéletes mása a bevezető szIntű \"nagytestvér\" a NetScroll 100X egérnek. Ahogy a fotón is látszik a NetScroll 310X kis mérettel és súllyal rendelkezik.', 6604, 'UM09-10-00823n.jpg'),
(8, 2147483647, '30 Multi-Colored Tulips', 'Nothing beats a big bunch of tulips fresh from the fields. These 30 tulips deliver an undeniably bright burst of color into any setting, whether it&#39;s a window sill, a country table, or your special someone&#39;s arms. A great gift for a 30th birthday!\n', 2286, 'PF_11_00000000M232_VA0211_W1_PF.jpg'),
(9, 7700000, 'Microsoft Egér Compact Optical 500 Black (U81-00017)', 'A NetScroll 310X egér tökéletes mása a bevezető szIntű \"nagytestvér\" a NetScroll 100X egérnek. Ahogy a fotón is látszik a NetScroll 310X kis mérettel és súllyal rendelkezik.', 3937, 'UM09-10-0237n.jpg'),
(10, 7700001, 'Toshiba Tablet Folio 100', 'A Toshiba Satellite® modellcsaládban változatos kijelzőméretűek a laptopok, a legkisebbtől a legnagyobbig, így mindenki megtalálhatja a számára legmegfelelőbbet. A mobilitást a kisméretű, könnyű laptopok biztosítják, amíg a nagyméretű kijelzővel rendelkező laptopok multimédiás feladatokra és irodai munkára készültek. A TruBrite® kijelző nagy fényerejű és széles látószögű, így káprázatos képminőséget biztosít a HD filmek és a fotók megjelenítésekor.', 82550, 'UM11-02-0069n.jpg'),
(11, 7700002, 'Toshiba Satellite Pro L500-1TX W7', 'A Toshiba Satellite® modellcsaládban változatos kijelzőméretűek a laptopok, a legkisebbtől a legnagyobbig, így mindenki megtalálhatja a számára legmegfelelőbbet. A mobilitást a kisméretű, könnyű laptopok biztosítják, amíg a nagyméretű kijelzővel rendelkező laptopok multimédiás feladatokra és irodai munkára készültek. A TruBrite® kijelző nagy fényerejű és széles látószögű, így káprázatos képminőséget biztosít a HD filmek és a fotók megjelenítésekor.', 85090, 'UM06-01-00261n.jpg'),
(12, 7700003, 'Tucano kiegészítő és táptartó tok (jégkék/szürke)', 'BFEF Easy Cable Pouch:\n	jégkék/szürke\n	szürke/szürke', 26670, 'UM08-12-0025n.jpg'),
(13, 7700004, 'Tucano mappa BFB13-R', 'Belső táskaméret: max. 13ʺ kijelzőjű laptophoz', 17780, 'UM08-08-0183n.jpg'),
(14, 7700005, 'Tucano laptop táska BASICP B - Computer Comforts Plus', 'Belső táskaméret: 37,5 x 30 x 4,5 cm\n	Külső táskaméret: 39 x 33 x 18 cm', 11430, 'UM10-13-123411n.jpg'),
(15, 7700006, 'Tucano laptop táska Youngster BNY-Y', 'Szín: sárga Belső táskaméret: max. 11.6ʺ kijelzőjű laptophoz', 11430, 'UM10-03-00285n.jpg'),
(16, 88000000, 'Egér USB optical Silver Spyker', 'A NetScroll 310X egér tökéletes mása a bevezető szIntű \"nagytestvér\" a NetScroll 100X egérnek. Ahogy a fotón is látszik a NetScroll 310X kis mérettel és súllyal rendelkezik.', 4064, 'UM09-10-00829n.jpg'),
(17, 88000001, 'Asus EEEPC 1001PX-WHI117S W7 2GB', 'Eee - Asus - Típus: Netbook, Processzor típusa: Intel Atom, Processzor órajel: 1.66 GHz, L2 cache mérete: 512 KB, Memória mérete: 1 GB, Memória típusa: DDR2, Kijelző mérete: 10.1\", Kijelző felbontása: 1024 x 600, Videókártya típusa: Integrált, 3D kijelző: Nem, Merevlemez típusa: HDD, Merevlemez kapacitása: 250 GB\nMemória: 2048\n', 152400, 'asus-eeepc1001w_0.jpg'),
(18, 88000002, 'Asus EEEPC 1015PEM-BLU048S W7', 'Eee - Asus - Típus: Netbook, Processzor típusa: Intel Atom, Processzor órajel: 1.66 GHz, L2 cache mérete: 512 KB, Memória mérete: 1 GB, Memória típusa: DDR2, Kijelző mérete: 10.1\", Kijelző felbontása: 1024 x 600, Videókártya típusa: Integrált, 3D kijelző: Nem, Merevlemez típusa: HDD, Merevlemez kapacitása: 250 GB\nMemória: 2048', 139700, 'UM11-03-0005n.jpg'),
(19, 88000003, 'Samsung N145-JP02HU White W7', 'A Samsung nagy hangsúlyt fektet arra, hogy a termékei és szolgáltatásai minden tekintetben professzionálisak legyenek, és értéket képviseljenek. Elkötelezett a környezetvédelem területén is, ezért olyan technológiákat fejleszt és alkalmaz termékeiben, amelyekkel csökkenthetőek a környezeti hatások. A termékek energiahatékonyságának növelése az ügyfeleknél jelentős megtakarítást eredményez. A Samsung hordozható számítógépek megfelelnek az Energy Star és EPEAT™ programok által kialakított tanúsítványrendszereknek és az RoHS irányelveknek. A Samsung netbookok rendelkeznek a környezet- és felhasználóbarát tervezést igazoló TCO tanúsítvánnyal', 146050, 'UM10-10-0113n.jpg'),
(20, 88000004, 'Samsung NS310-A01HU Blue W7', 'A Samsung nagy hangsúlyt fektet arra, hogy a termékei és szolgáltatásai minden tekintetben professzionálisak legyenek, és értéket képviseljenek. Elkötelezett a környezetvédelem területén is, ezért olyan technológiákat fejleszt és alkalmaz termékeiben, amelyekkel csökkenthetőek a környezeti hatások. A termékek energiahatékonyságának növelése az ügyfeleknél jelentős megtakarítást eredményez. A Samsung hordozható számítógépek megfelelnek az Energy Star és EPEAT™ programok által kialakított tanúsítványrendszereknek és az RoHS irányelveknek. A Samsung netbookok rendelkeznek a környezet- és felhasználóbarát tervezést igazoló TCO tanúsítvánnyal', 165100, 'UM11-04-0058n.jpg'),
(21, 88000005, 'HP Mini 210-2200eh LD224EA Preppy Pink', '', 120650, 'UM11-06-0001n.jpg'),
(22, 88000006, 'HP G62-B30EH XR499EA Silver LX', '	Az alábbi hardveres képességek segítik a rendszer hatékonyabb működését:\n	- Az AMD HyperTransport™ Technology képességű AMD processzor nagysebességű, alacsony válaszidejű pont-pont összeköttetéssel rendelkezik, amely megfelelő sávszélességet biztosít a processzor, az I/O alrendszerek, a memóriák és egyéb vezérlők között.\n	- Az AMD Virtualization™ Technology (AMD-V™) képességű AMD processzor virtualizációs rendszerben működve növeli annak teljesítményét a tisztán szoftveres megoldásokhoz képest.\n	- Az AMD64 Technology képességű AMD processzor 4GB-nál több memória megcímzésére képes, ezáltal elérhetővé válnak a 64 bites operációs rendszerek és programok által nyújtott előnyök.', 116840, 'UM10-08-5006n.jpg');
");