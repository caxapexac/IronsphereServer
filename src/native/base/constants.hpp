#ifndef LOGIC_CONSTANTS_HPP
#define LOGIC_CONSTANTS_HPP

/// For the sake of readability. This freaking language just doesn't support attributes.
/// God damn I'm creating serialization without reflection
/// Path to clearing your soul:
/// Learn c++
/// Break up with a girl
/// Make useless define
#define N_S /*Non serialized*/
/// *You are here*
/// <doctype=html />
/// Delet yuself
/// Epik vin

#define OBSOLETE /*Obsolete*/

//TODO all strings into enum constants
//TODO add common constants (generic RTS)
//TODO uint -> int ?
namespace constants {
    const int version = 100; // Game version (Anti chEET)
    const int lobby_delta_time = 1000; // ms (start game loop delay)
    const char game_title[] = "Ironsphere";
    const unsigned int player_units_limit = 100;
    const unsigned int neutral_units_limit = 25;
}

enum loggers {
    server_console_logger = 1, all_clients_logger = 2, server_file_logger = 4
};

enum streams : char {
    error = 'E', warning = 'W', debug = 'D', message = 'M', special = 'S'
};

// TODO into class

//TODO L4-5 without json ;(

/*Patterns
 * L1 Unit attributes, abilities (components(?)) (?)
 * L1 Create Unit (factory/abstract factory)
 * L2 Store unit get_info (composite) is json legal?
 * L2 Get unit in base (observer) events subscribe
 * L2 Tilemap - Unit (proxy)
 * L2 Neutral - Unit (strategy)
 * STARTED L3 Input (facade)
 * L3 Unit - Unit (mediator)
 * L3 Input - Unit (command)
 * L3 User - Unit (chain of responsibility)
 * STARTED L4 Logging level (proxy)
 * L4 Logging format (adapter)
 * STARTED L5 Save/Load (memento) is json legal?
 * L6 Player1 - Player2 - Player1 (State) idk how cuz we have RTS
 * L6 Game class (singleton)
 * L7
 * Other
 */


/***
 * По десереализации можно написать класс,
 * который начинает парсить строку, например
 * первый символ означает какой класс. После
 * проверки первого символа создает необходимый
 * класс десереализации под конкретного юнита
 * (что-то по типу паттерна стратегия) и возвращает
 * восстановленный объект класса
 *
 * Можно создать класс, в котором есть map,
 * с ассоциацией символа и класса конкретной десереализции
 *
 * Есть общий класс десериализатора, который начинает
 * первым парсить строку. В этом классе, есть map,
 * который связывает тип и объект конкретного
 * десериализатора. Собственно, общий класс считывает
 * информацию, чтобы понять что за класс, по этой
 * информации достает из map необходимый десереализатор,
 * который будет завершать парсинг строки и
 * возвращать объект уже нужного класса
 *
 * можно сделать класс прослойку, который из строки
 * достает необходимые параметры, у уже вызывает
 * конструктор юнита с необходимыми параметрами.
 * Таким образом, мы избавляем класс юнита от необходимости
 * знать, каким образом и откуда он создается
 *
 * Вариант №2, узнавать размер класса, читать байты
 * из памяти напрямую и их сохранять, а при восстановлении
 * выделить нужную память и туда записывать байты
 ***/

#endif //LOGIC_CONSTANTS_HPP
