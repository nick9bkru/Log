#!/bin/bash
# Клиент обменивается командами через FIFO файл созданный програмой server
#
#FIFO файл для обмена с сервером командами
FIFO_FROM_S='./FIFO_FROM_S'$$
FIFO_TO_S='./FIFO_TO_S'$$
########################################################################################
rmFifo()
{
    rm -f $FIFO_FROM_S
    rm -f $FIFO_TO_S 
}
########################################################################################
mainmenu()
{
    clear
    echo "Добро пажаловать в программу управления камерой"
    echo "1) Управление состоянием LED камеры"
    echo "2) Узнать состояние LED камеры"
    echo "3) Изменить цвет LED"
    echo "4) Запросить цвет LED"
    echo "5) Изменить частоту мерцание LED"
    echo "6) Запросить частоту мерцания LED"
    echo "7) Выход"
    read -p "Введите номер пункта меню: " -n 1 ans
    case $ans in 
      '1' ) menuSetLed;;
      '2' ) menuGetLed;;
      '3' ) menuSetColor;;
      '4' ) menuGetColor;;
      '5' ) menuSetRate;;
      '6' ) menuGetRate;;
      '7' ) rmFifo 
	    exit 0;;
      * )mainmenu ;;
    esac
}
########################################################################################
menuSetLed()
{
    clear
    echo "Меню управления LED "
    echo "1) Включить LED"
    echo "2) ВыключитьLED "
    echo "3) Назад "
    read -p "Введите номер пункта меню: " -n 1 ans
	case $ans in 
	  '1' ) cmd="on";;
	  '2' ) cmd="off";;
	  '3' ) mainmenu;;
	  * ) menuSetLed ;;
	esac
    WriteRead "set-led-state " $cmd
    echo ""
    echo "Выполнение команды :"$ret 
    read -n 1
    mainmenu
}
########################################################################################
menuGetLed()
{
 clear
 cmd="get-led-state"
 WriteRead $cmd
 ret=${ret/OK on/Включена}
 ret=${ret/OK off/Выключена}
 echo "Состояние LED камеры : "$ret 
 read -n 1
 mainmenu
}
########################################################################################
menuSetColor()
{
    clear
    echo "Меню управления цветом LED "
    echo "Установить цвет LED в : "
    echo "1) Красный"
    echo "2) Зеленый "
    echo "3) Синий "
    echo "4) Назад "
    read -p "Введите номер пункта меню: " -n 1 ans
    case $ans in 
      '1' ) cmd="red";;
      '2' ) cmd="green";;
      '3' ) cmd="blue";;
      '4' ) mainmenu;;
      * ) menuSetLed ;;
    esac
    WriteRead "set-led-color "$cmd
    echo ""
    echo "Выполнение команды :"$ret
    read -n 1
    mainmenu
}
########################################################################################
menuGetColor()
{
 clear
 cmd="get-led-color"
 WriteRead $cmd
 ret=${ret/OK red/Красный}
 ret=${ret/OK green/Зеленый}
 ret=${ret/OK blue/Синий}
 echo "Цвет LED камеры :" $ret 
  read -n 1
 mainmenu
}
########################################################################################
menuSetRate()
{
    clear
    echo "Меню частотой мерцания LED "
    read -p "Введите частоту ( 0..5 ) (либо b для возвращения в предыдущее меню): " -n 1 ans
    case $ans in 
	  [0-5] ) ;;
	  'b' ) mainmenu;;
	   * ) menuSetLed ;;
	esac
    WriteRead "set-led-rate "$ans
    echo ""
    echo "Выполнение команды :"$ret
    read -n 1
    mainmenu
}
########################################################################################
menuGetRate()
{
 clear
 cmd="get-led-rate"
 WriteRead $cmd
 ret=${ret#OK}
 echo "Частота мерцания LED камеры :" $ret
 read -n 1
 mainmenu
}
########################################################################################
WriteRead() 
{
    cmd=`echo $1$2`
    echo $cmd > $FIFO_TO_S
    read ret < $FIFO_FROM_S
}
########################################################################################
rmFifo ##удаляем старые файлы если такие имеются

mkfifo $FIFO_FROM_S
mkfifo $FIFO_TO_S
mainmenu
########################################################################################
########################################################################################
########################################################################################
exit 0
echo "Enter command for camera :"
read cmd
echo "write command to FIFO file ..."
echo $cmd > $FIFO_TO_S
echo "waiting for a answer from the server ..."
read ans < $FIFO_FROM_S
echo "The answer from the server is "$ans

rm -f $FIFO_FROM_S
rm -f $FIFO_TO_S 