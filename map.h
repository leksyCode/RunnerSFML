#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>


		const int HEIGHT_MAP = 15;
		const int WIDTH_MAP = 85;
			sf::String TileMap[HEIGHT_MAP] = {
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
				"0                      h              s f                                       sssss",
				"0                   f                                                           sssss",
				"0                                              h                                sssss",
				"0                             s f                                              eessss",
				"0                                                                        f     eeesss",
				"0                                                                              eeesss",
				"0                                           s  h     f                         eeesss",
				"0                                                                              eessss",
				"0             s                                    s                            sssss",
				"0             s   fh                        s        f                   f      sssss",
				"0             s                                                                 sssss",
				"0                                       f                                       sssss",
				"0                      h                                                        sssss",
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
			};
			sf::String TileMapBackUp[HEIGHT_MAP] = {
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
				"0                      h              s f                                       sssss",
				"0                   f                                                           sssss",
				"0                                              h                                sssss",
				"0                             s f                                              eessss",
				"0                                                                        f     eeesss",
				"0                                                                              eeesss",
				"0                                           s  h     f                         eeesss",
				"0                                                                              eessss",
				"0             s                                    s                            sssss",
				"0             s   fh                        s        f                   f      sssss",
				"0             s                                                                 sssss",
				"0                                       f                                       sssss",
				"0                      h                                                        sssss",
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
			};
			sf::String TileMapLvl1[HEIGHT_MAP] = {
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
				"0                                     s f                                       sssss",
				"0         s         f                                              h            sssss",
				"0                                           s                 s  s  s           sssss",
				"0             s               s f                             s       s        eessss",
				"0                                   h                                    f     eeesss",
				"0                 s                                                            eeesss",
				"0                                           s  h     f              s          eeesss",
				"0                                  s                          s                eessss",
				"0             s s                    s            s                             sssss",
				"0             s                            s        f             s     f       sssss",
				"0             s                    s                                            sssss",
				"0                f                      f                     s                 sssss",
				"0                       h                                              h        sssss",
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
			};
			sf::String TileMapLvl2[HEIGHT_MAP] = {
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
				"0                      h              s f                           f           sssss",
				"0                   f                                                           sssss",
				"0                                              h                                sssss",
				"0                             s f                                              eessss",
				"0                                                                        f     eeesss",
				"0                    s h    f             s                                    eeesss",
				"0            s   s    s h                      s                               eeesss",
				"0                 h   s h        f                   s                         eessss",
				"0                     s  h  f          h                   s                    sssss",
				"0              h        h                     f     f            s              sssss",
				"0                    s h f     f       h                h     s                 sssss",
				"0              ss  h s h          f       h      h            h          s      sssss",
				"0                    s h   f                         f     ss  f                sssss",
				"00000000000000000000000000000000000000000000000000000000000000000000000000000000sssss",
			};
			sf::String TileMapLvl3[HEIGHT_MAP] = {
				"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
				"0                      h              s f                                       ssss0",
				"0                   f                                            f              ssss0",
				"0                                              h                                ssss0",
				"0                 h           s f                                                sss0",
				"0                                               s   ss       s    s     f         ss0",
				"0                      s                     ss                                   ss0",
				"0                       s                        h   f   h     f  h   f           ss0",
				"0                       s  s  s   s  s   s   f            ss     s                ss0",
				"0                        s   h      h      h       ss                s   s      ssss0",
				"0                       s       h   f    f    s                                 ssss0",
				"0                      s     h      h                                           ssss0",
				"0                      s     s    ss    ss                                      ssss0",
				"0                      s                                                        ssss0",
				"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
			};


			void randomMapGenerate() {//рандомно расставляем камни
				int randomElementX = 0;//случайный элемент по горизонтали
				int randomElementY = 0;//случ эл-т по вертикали
				srand(time(0));//рандом	
				int countStone = 40;//количество камней
				while (countStone>0) {
					randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
					randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же
					if (TileMap[randomElementY][randomElementX] == ' ') {//если встретили символ пробел, 
						TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.
																	   //std::cout << "coordinate of Stone X:" << randomElementX << "\n" << "coordinate of Stone Y:" << randomElementY << "\n\n";
						countStone--;
					}
				}
			}
#endif //MAP_H

		
	