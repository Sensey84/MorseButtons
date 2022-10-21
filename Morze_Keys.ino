/******************************************************************************
    Проект воспроизведения кодов Морзе для стенда
    На стенде отдельно реализована каждая кнопка
    для воспроизведения указанных на стенде кодов
    азбуки Морзе.
 ******************************************************************************
    Кнопки подключаются в виде матрицы кнопок с использованием
    диодов, которые подключены в линии строк матрицы, т.е.
    количество кнопок равно количеству диодов.
    Подтягивающие резисторы установлены линии столбцов матрицы.
    Все кнопки без фиксации, подавление дребезга контактов
    реализовано программно. Кнопки можно использовать любые,
    нормально открытые (NO).
 ******************************************************************************
    Матрица кнопок состоит из 6 строк и 7 столбцов, всего 42 кнопки.
    Светодиод для дополнительной индикации можно подключить на вывод
    12, к которому подключен внешний транзистор для увеличения
    нагрузочной способности.
    На выход 13 подключен внешний транзистор для подключения звукового
    элемента (пьезоизлучатель, маломощный динамик т.п.).
 ******************************************************************************/

#include <Arduino.h>
#include <Keypad.h>
//#include "button.h"        // раскомментировать для отладки

//#define BUTT_KEY 11        // кнопка для ключа D11 (раскомментировать для отладки)
#define LED 9               // диод на плате, можно подключить вненший на пин D9
#define SIG_OUT 10          // пин подключения зуммера D10
#define SIG_TM 100          // длительность в миллисекундах для работы с временем для точки и тире
#define ROWS 6              // количество строк клавиатуры
#define COLS 7              // количество столбцов клавиатуры

// Для проверки подсоединить кнопку на пин D11 и раскомментировать нужные строки
//button But_1(BUTT_KEY);     // раскомментировать для отладки

// Задаём матрицу кнопок, всего 42 кнопки
char Morze_Keys[ROWS][COLS] =
{
  {'0', '1', '2', '3', '4', '5', '6'},
  {'7', '8', '9', '10', '11', '12', '13'},
  {'14', '15', '16', '17', '18', '19', '20'},
  {'21', '22', '23', '24', '25', '26', '27'},
  {'28', '29', '30', '31', '32', '33', '34'},
  {'35', '36', '37', '38', '39', '40', '41'}
};

uint8_t rowPins[ROWS] = {14, 15, 16, 17, 18, 19}; // подсоединяем строки клавиатуры к пинам Arduino
uint8_t colPins[COLS] = {2, 3, 4, 5, 6, 7, 8};    // подсоединяем столбцы клавиатуры к пиналм Arduino

// Инициализация клавиатуры из класса библиотеки Keypad
Keypad MorzeKeypad = Keypad(makeKeymap(Morze_Keys), rowPins, colPins, ROWS, COLS);

// Сохраняем во FLASH коды азбуки Морзе, использованы будут 42 последовательности
// символы русского(латинского) алфавита и цифры от 0 до 9.

const char Code0 [] PROGMEM = {"13000000"};    //    А                  A        . -          ай-даа, ай-ваа
const char Code1 [] PROGMEM = {"31110000"};    //    Б                  B        - . . .      баа-ки-те-кут, беей-ба-ра-бан
const char Code2 [] PROGMEM = {"13300000"};    //    В                  W        . - -        ви-даа-лаа, вол-чаа-таа
const char Code3 [] PROGMEM = {"33100000"};    //    Г                  G        - - .        гаа-раа-жи, гаа-гаа-рин
const char Code4 [] PROGMEM = {"31100000"};    //    Д                  D        - . .        доо-ми-ки, даай-ку-рить
const char Code5 [] PROGMEM = {"10000000"};    //    Е (также и Ё)      E        .            есть
const char Code6 [] PROGMEM = {"11130000"};    //    Ж                  V        . . . -      же-ле-зис-тоо
const char Code7 [] PROGMEM = {"33110000"};    //    З                  Z        - - . .      заа-каа-ти-ки
const char Code8 [] PROGMEM = {"11000000"};    //    И                  I        . .          и-ди, ишь-ты
const char Code9 [] PROGMEM = {"13330000"};    //    Й                  J        . - - -      йес-наа-паа-раа, йош-каа-роо-лаа
const char Code10 [] PROGMEM = {"31300000"};   //    К                  K        - . -        каак-же-таак, каак-де-лаа
const char Code11 [] PROGMEM = {"13110000"};   //    Л                  L        . - . .      лу-наа-ти-ки
const char Code12 [] PROGMEM = {"33000000"};   //    М                  M        - -          маа-маа
const char Code13 [] PROGMEM = {"31000000"};   //    Н                  N        - .          ноо-мер, наа-те
const char Code14 [] PROGMEM = {"33300000"};   //    О                  O        - - -        оо-коо-лоо
const char Code15 [] PROGMEM = {"13310000"};   //    П                  P        . - - .      пи-лаа-поо-ёт
const char Code16 [] PROGMEM = {"13100000"};   //    Р                  R        . - .        ре-шаа-ет, ру-каа-ми
const char Code17 [] PROGMEM = {"11100000"};   //    С                  S        . . .        си-ни-е, си-не-е, са-мо-лёт
const char Code18 [] PROGMEM = {"30000000"};   //    Т                  T        -            таак, таам
const char Code19 [] PROGMEM = {"11300000"};   //    У                  U        . . -        у-нес-лоо, у-бе-гуу
const char Code20 [] PROGMEM = {"11310000"};   //    Ф                  F        . . - .      фи-ли-моон-чик
const char Code21 [] PROGMEM = {"11110000"};   //    Х                  H        . . . .      хи-ми-чи-те
const char Code22 [] PROGMEM = {"31310000"};   //    Ц                  C        - . - .      цаа-пли-наа-ши, цаа-пли-цаа-пли
const char Code23 [] PROGMEM = {"33310000"};   //    Ч                  Ö        - - - .      чаа-шаа-тоо-нет, чее-лоо-вее-чек
const char Code24 [] PROGMEM = {"33330000"};   //    Ш                  CH        - - - -     шаа-роо-ваа-рыы, шуу-раа-доо-маа
const char Code25 [] PROGMEM = {"33130000"};   //    Щ                  Q        - - . -      щаа-ваам-не-шаа, щуу-каа-жи-ваа
const char Code26 [] PROGMEM = {"33133000"};   //    Ъ                  Ñ        - - . - -    твёёр-дыый-не-мяяг-киий
const char Code27 [] PROGMEM = {"31330000"};   //    Ы                  Y        - . - -      ыы-не-наа-доо
const char Code28 [] PROGMEM = {"31130000"};   //    Ь (также и Ъ)      X        - . . -      тоо-мяг-кий-знаак, знаак-мяг-кий-знаак
const char Code29 [] PROGMEM = {"11311000"};   //    Э                  É        . . - . .    э-ле-роо-ни-ки, э-ле-ктроо-ни-ка
const char Code30 [] PROGMEM = {"11330000"};   //    Ю                  Ü        . . - -      ю-ли-аа-наа
const char Code31 [] PROGMEM = {"13130000"};   //    Я                  Ä        . - . -      я-маал-я-маал
const char Code32 [] PROGMEM = {"13333000"};   //    1   . - - - -      и-тооль-коо-оо-днаа
const char Code33 [] PROGMEM = {"11333000"};   //    2   . . - - -      две-не-хоо-роо-шоо
const char Code34 [] PROGMEM = {"11133000"};   //    3   . . . - -      три-те-бе-маа-лоо
const char Code35 [] PROGMEM = {"11113000"};   //    4   . . . . -      че-тве-ри-те-каа
const char Code36 [] PROGMEM = {"11111000"};   //    5   . . . . .      пя-ти-ле-ти-е
const char Code37 [] PROGMEM = {"31111000"};   //    6   - . . . .      поо-шес-ти-бе-ри
const char Code38 [] PROGMEM = {"33111000"};   //    7   - - . . .      даа-даа-се-ме-ри
const char Code39 [] PROGMEM = {"33311000"};   //    8   - - - . .      воо-сьмоо-гоо-и-ди
const char Code40 [] PROGMEM = {"33331000"};   //    9   - - - - .      ноо-наа-ноо-наа-ми
const char Code41 [] PROGMEM = {"33333000"};   //    0   - - - - -      нооль-тоо-оо-коо-лоо
const char Code42 [] PROGMEM = {"11111100"};   //    Точка                    . . . . . .        то-чеч-ка-то-чеч-ка
const char Code43 [] PROGMEM = {"13131300"};   //    Запятая                  . - . - . -        крю-чоок-крю-чоок-крю-чоок
const char Code44 [] PROGMEM = {"33311100"};   //    Двоеточие                - - - . . .        двоо-ее-тоо-чи-е-ставь
const char Code45 [] PROGMEM = {"31313100"};   //    Точка с запятой          - . - . - .        тоо-чка-заа-пя-таа-я
const char Code46 [] PROGMEM = {"31331300"};   //    Скобка                   - . - - . -        скоо-бку-стаавь-скоо-бку-стаавь, скоо-бку-тыы-мнее-пи-шии
const char Code47 [] PROGMEM = {"13333100"};   //    Апостроф                 . - - - - .        крю-чоок-тыы-веерх-ниий-ставь
const char Code48 [] PROGMEM = {"13113100"};   //    Кавычки                  . - . . - .        ка-выы-чки-ка-выы-чки, ка-выы-чки-от-крыы-ли, ка-выы-чки-за-крыы-ли
const char Code49 [] PROGMEM = {"31111300"};   //    Тире                     - . . . . -        чёёр-точ-ку-мне-да-ваай, чёёр-точ-ку-ты-пи-шии
const char Code50 [] PROGMEM = {"31131000"};   //    Косая черта              - . . - .          дрообь-здесь-пред-стаавь-те, доо-ми-ки-ноо-мер
const char Code51 [] PROGMEM = {"11331100"};   //    Вопросительный знак      . . - - . .        вы-ку-даа-смоо-три-те, до-про-сии-лии-е-го, у-нес-лоо-доо-ми-ки, э-ти-воо-проо-си-ки
const char Code52 [] PROGMEM = {"33113300"};   //    Восклицательный знак     - - . . - -        оо-наа-вос-кли-цаа-лаа
const char Code53 [] PROGMEM = {"31113000"};   //    Знак раздела             - . . . -          рааз-де-ли-те-каа
const char Code54 [] PROGMEM = {"11111111"};   //    Ошибка/перебой           . . . . . . . .    хи-ми-чи-те-хи-ми-чи-те, ше-стью-во-семь-со-рок-во-семь
const char Code55 [] PROGMEM = {"13313100"};   //    @                        . - - . - .        со-баа-каа-ре-шаа-ет, со-баа-каа-ку-саа-ет
const char Code56 [] PROGMEM = {"11313000"};   //    Конец связи              . . - . -          хо-ро-шоо-по-каа, хо-ро-шоо-да-ваай, до-сви-даа-ни-яя

// Таблица ссылок на шифры

PGM_P const Codes[] PROGMEM = {
  Code0, Code1, Code2, Code3, Code4, Code5, Code6, Code7, Code8, Code9,
  Code10, Code11, Code12, Code13, Code14, Code15, Code16, Code17, Code18, Code19,
  Code20, Code21, Code22, Code23, Code24, Code25, Code26, Code27, Code28, Code29,
  Code30, Code31, Code32, Code33, Code34, Code35, Code36, Code37, Code38, Code39,
  Code40, Code41, Code42, Code43, Code44, Code45, Code46, Code47, Code48, Code49,
  Code50, Code51, Code52, Code53, Code54, Code55, Code56
};

// Таблица расшифровок кодов Морзе, хранится во FLASH. 
//При включении контроллера отправляется вся таблица в последовательный порт один раз

const char String0 [] PROGMEM =  {"  А      |       A   | . -       | ай-даа, ай-ваа"};
const char String1 [] PROGMEM =  {"  Б      |       B   | - . . .   | баа-ки-те-кут, беей-ба-ра-бан"};
const char String2 [] PROGMEM =  {"  В      |       W   | . - -     | ви-даа-лаа, вол-чаа-таа"};
const char String3 [] PROGMEM =  {"  Г      |       G   | - - .     | гаа-раа-жи, гаа-гаа-рин"};
const char String4 [] PROGMEM =  {"  Д      |       D   | - . .     | доо-ми-ки, даай-ку-рить"};
const char String5 [] PROGMEM =  {"  Е (также и Ё)| E   | .         | есть"};
const char String6 [] PROGMEM =  {"  Ж      |       V   | . . . -   | же-ле-зис-тоо"};
const char String7 [] PROGMEM =  {"  З      |       Z   | - - . .   | заа-каа-ти-ки"};
const char String8 [] PROGMEM =  {"  И      |       I   | . .       | и-ди, ишь-ты"};
const char String9 [] PROGMEM =  {"  Й      |       J   | . - - -   | йес-наа-паа-раа, йош-каа-роо-лаа"};
const char String10 [] PROGMEM = {"  К      |       K   | - . -     | каак-же-таак, каак-де-лаа"};
const char String11 [] PROGMEM = {"  Л      |       L   | . - . .   | лу-наа-ти-ки"};
const char String12 [] PROGMEM = {"  М      |       M   | - -       | маа-маа"};
const char String13 [] PROGMEM = {"  Н      |       N   | - .       | ноо-мер, наа-те"};
const char String14 [] PROGMEM = {"  О      |       O   | - - -     | оо-коо-лоо"};
const char String15 [] PROGMEM = {"  П      |       P   | . - - .   | пи-лаа-поо-ёт"};
const char String16 [] PROGMEM = {"  Р      |       R   | . - .     | ре-шаа-ет, ру-каа-ми"};
const char String17 [] PROGMEM = {"  С      |       S   | . . .     | си-ни-е, си-не-е, са-мо-лёт"};
const char String18 [] PROGMEM = {"  Т      |       T   | -         | таак, таам"};
const char String19 [] PROGMEM = {"  У      |       U   | . . -     | у-нес-лоо, у-бе-гуу"};
const char String20 [] PROGMEM = {"  Ф      |       F   | . . - .   | фи-ли-моон-чик"};
const char String21 [] PROGMEM = {"  Х      |       H   | . . . .   | хи-ми-чи-те"};
const char String22 [] PROGMEM = {"  Ц      |       C   | - . - .   | цаа-пли-наа-ши, цаа-пли-цаа-пли"};
const char String23 [] PROGMEM = {"  Ч      |       Ö   | - - - .   | чаа-шаа-тоо-нет, чее-лоо-вее-чек"};
const char String24 [] PROGMEM = {"  Ш      |       CH  | - - - -   | шаа-роо-ваа-рыы, шуу-раа-доо-маа"};
const char String25 [] PROGMEM = {"  Щ      |       Q   | - - . -   | щаа-ваам-не-шаа, щуу-каа-жи-ваа"};
const char String26 [] PROGMEM = {"  Ъ      |       Ñ   | - - . - - | твёёр-дыый-не-мяяг-киий"};
const char String27 [] PROGMEM = {"  Ы      |       Y   | - . - -   | ыы-не-наа-доо"};
const char String28 [] PROGMEM = {"  Ь (также и Ъ)| X   | - . . -   | тоо-мяг-кий-знаак, знаак-мяг-кий-знаак"};
const char String29 [] PROGMEM = {"  Э      |       É   | . . - . . | э-ле-роо-ни-ки, э-ле-ктроо-ни-ка"};
const char String30 [] PROGMEM = {"  Ю      |       Ü   | . . - -   | ю-ли-аа-наа"};
const char String31 [] PROGMEM = {"  Я      |       Ä   | . - . -   | я-маал-я-маал"};
const char String32 [] PROGMEM = {"  1   | . - - - - |  и-тооль-коо-оо-днаа"};
const char String33 [] PROGMEM = {"  2   | . . - - - |  две-не-хоо-роо-шоо"};
const char String34 [] PROGMEM = {"  3   | . . . - - |  три-те-бе-маа-лоо"};
const char String35 [] PROGMEM = {"  4   | . . . . - |  че-тве-ри-те-каа"};
const char String36 [] PROGMEM = {"  5   | . . . . . |  пя-ти-ле-ти-е"};
const char String37 [] PROGMEM = {"  6   | - . . . . |  поо-шес-ти-бе-ри"};
const char String38 [] PROGMEM = {"  7   | - - . . . |  даа-даа-се-ме-ри"};
const char String39 [] PROGMEM = {"  8   | - - - . . |  воо-сьмоо-гоо-и-ди"};
const char String40 [] PROGMEM = {"  9   | - - - - . |  ноо-наа-ноо-наа-ми"};
const char String41 [] PROGMEM = {"  0   | - - - - - |  нооль-тоо-оо-коо-лоо"};
const char String42 [] PROGMEM = {"  Точка                | . . . . . .     |  то-чеч-ка-то-чеч-ка"};
const char String43 [] PROGMEM = {"  Запятая              | . - . - . -     |  крю-чоок-крю-чоок-крю-чоок"};
const char String44 [] PROGMEM = {"  Двоеточие            | - - - . . .     |  двоо-ее-тоо-чи-е-ставь"};
const char String45 [] PROGMEM = {"  Точка с запятой      | - . - . - .     |  тоо-чка-заа-пя-таа-я"};
const char String46 [] PROGMEM = {"  Скобка               | - . - - . -     |  скоо-бку-стаавь-скоо-бку-стаавь, скоо-бку-тыы-мнее-пи-шии"};
const char String47 [] PROGMEM = {"  Апостроф             | . - - - - .     |  крю-чоок-тыы-веерх-ниий-ставь"};
const char String48 [] PROGMEM = {"  Кавычки              | . - . . - .     |  ка-выы-чки-ка-выы-чки, ка-выы-чки-от-крыы-ли, ка-выы-чки-за-крыы-ли"};
const char String49 [] PROGMEM = {"  Тире                 | - . . . . -     |  чёёр-точ-ку-мне-да-ваай, чёёр-точ-ку-ты-пи-шии"};
const char String50 [] PROGMEM = {"  Косая черта          | - . . - .       |  дрообь-здесь-пред-стаавь-те, доо-ми-ки-ноо-мер"};
const char String51 [] PROGMEM = {"  Вопросительный знак  | . . - - . .     |  вы-ку-даа-смоо-три-те, до-про-сии-лии-е-го, у-нес-лоо-доо-ми-ки, э-ти-воо-проо-си-ки"};
const char String52 [] PROGMEM = {"  Восклицательный знак | - - . . - -     |  оо-наа-вос-кли-цаа-лаа"};
const char String53 [] PROGMEM = {"  Знак раздела         | - . . . -       |  рааз-де-ли-те-каа"};
const char String54 [] PROGMEM = {"  Ошибка/перебой       | . . . . . . . . |  хи-ми-чи-те-хи-ми-чи-те, ше-стью-во-семь-со-рок-во-семь"};
const char String55 [] PROGMEM = {"  @                    | . - - . - .     |  со-баа-каа-ре-шаа-ет, со-баа-каа-ку-саа-ет"};
const char String56 [] PROGMEM = {"  Конец связи          | . . - . -       |  хо-ро-шоо-по-каа, хо-ро-шоо-да-ваай, до-сви-даа-ни-яя"};

// Таблица ссылок на коды расшифровок

PGM_P const Strings[] PROGMEM = {
  String0, String1, String2, String3, String4, String5, String6, String7, String8, String9,
  String10, String11, String12, String13, String14, String15, String16, String17, String18, String19,
  String20, String21, String22, String23, String24, String25, String26, String27, String28, String29,
  String30, String31, String32, String33, String34, String35, String36, String37, String38, String39,
  String40, String41, String42, String43, String44, String45, String46, String47, String48, String49,
  String50, String51, String52, String53, String54, String55, String56
};

void GenerateTone(char Key_in);
void ButtonClock();
void PrintCodes();

void setup()
{
  Serial.begin(9600);
  PrintCodes();
  pinMode(LED, OUTPUT);
  pinMode(SIG_OUT, OUTPUT);
  //  pinMode(BUTT_KEY, INPUT_PULLUP);
}

void loop()
{
  /*
    static uint8_t Morze_Code = 0;        // строки для отладки схемы

    if (But_1.click())
    {
      Serial.print("Code_in: ");
      Serial.println(Morze_Code);
      GenerateTone(Morze_Code);
      Morze_Code++;
      if (Morze_Code > 56)
      {
        Morze_Code = 0;
      }
    }
  */

  char M_Key = MorzeKeypad.getKey();      // При нажатии на кнопку, функция определяет номер кнопки
  if (M_Key) GenerateTone(M_Key);         // и вызывает генерацию выбранного кода
}

/******************************************************************************
                      Функция генерирования сигнала
 ******************************************************************************
   к пину SIG_OUT подключать пьезоизлучатель
   к пину LED подключать светодиод
   Функция генерирует на выходах SIG_OUT и LED последовательность кодов Морзе
   длительность (по умолчанию):
   точка 100 мс
   тире 3*100 мс
   пауза 100 мс
 ******************************************************************************/

void GenerateTone(char Key_in)
{
  for (uint16_t x = 0; x < strlen_P(pgm_read_word(&(Codes[(uint8_t)Key_in]))); x++)
  {
    digitalWrite(LED, HIGH);                              // включить светодиод и зуммер на время из кода
    digitalWrite(SIG_OUT, HIGH);
    char dataIn = (char)pgm_read_byte_near(pgm_read_word(&(Codes[(uint8_t)Key_in])) + x);
    if (dataIn == '1') delay(1 * SIG_TM);                 // если код соответствует точке, тогда длительность 100 мс
    if (dataIn == '3') delay(3 * SIG_TM);                 // если код соответствует тире, тогда длительность 300 мс
    digitalWrite(LED, LOW);                               // отключить светодиод и зуммер на время из кода
    digitalWrite(SIG_OUT, LOW);
    delay(SIG_TM);                                        // пауза между символами 100 мс
  }
}

/******************************************************************************
       Функция печати в последовательный порт таблицы кодов Морзе
 ******************************************************************************
   56 кодов с расшифровкой
 ******************************************************************************/

void PrintCodes()
{
  for (uint8_t i = 0; i < 57; i++)
  {
    Serial.print("Code ");
    Serial.print(i);
    if (i < 10) Serial.print(":  ");
    else Serial.print(": ");

    for (uint16_t j = 0; j < strlen_P(pgm_read_word(&(Strings[i]))); j++)
    {
      char dataIn = (char)pgm_read_byte_near(pgm_read_word(&(Strings[i])) + j);      // определяем код команды из таблицы
      Serial.print(dataIn);
    }
    Serial.println("");
  }
}
