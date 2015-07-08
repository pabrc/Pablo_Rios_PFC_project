library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity multiplex_salida is
    Port ( async_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
			  in0,in1,in2,in3,in4,in5,in6,in7,in8,in9,in10,in11,in12,in13,in14 : in  STD_LOGIC_VECTOR (31 downto 0);
           sel : in  STD_LOGIC_VECTOR (3 downto 0);
           sync_reset : in  STD_LOGIC;
           q : out  STD_LOGIC_VECTOR(31 downto 0) );
end multiplex_salida;

architecture Behavioral of multiplex_salida is

begin

process (async_reset,en,sel,sync_reset,in0,in1,in2,in3,in4,in5,in6,in7,in8,in9,in10,in11,in12,in13)
begin
   if async_reset ='1' then   
      q <= X"00000000";
   elsif   sync_reset = '1' then 
         q<= X"00000000";
	elsif en = '1'	then 
	
		CASE sel IS
		
    WHEN  "0000"  =>  q <= in0;  --visualizo en la salida registro de configuracion
    WHEN  "0001"  =>  q <= in1;	--visualizo en la salida timer
    WHEN  "0010"  =>  q <= in2;	--visualizo en la salida Peridodo del PWM
    WHEN  "0011"  =>  q <= in3;	--visualizo en la salida Ton del PWM
	 WHEN  "0100"  =>  q <= in4;	--visualizo en la salida valor comparacion_0
	 WHEN  "0101"  =>  q <= in5;	--visualizo en la salida valor comparacion_1
	 WHEN  "0110"  =>  q <= in6;	--visualizo en la salida valor comparacion_2
	 WHEN  "0111"  =>  q <= in7;	--visualizo en la salida valor comparacion_3
	 WHEN  "1000"  =>  q <= in8;	--visualizo en la salida valor comparacion_4
	 WHEN  "1001"  =>  q <= in9;	--visualizo en la salida valor Captura_0
	 WHEN  "1010"  =>  q <= in10;	--visualizo en la salida valor Captura_1
	 WHEN  "1011"  =>  q <= in11;	--visualizo en la salida valor Captura_2
	 WHEN  "1100"  =>  q <= in12; --visualizo en la salida valor Captura_3
	 WHEN  "1101"  =>  q <= in13; --visualizo en la salida valor Captura_4
	 WHEN  "1110"  =>  q <= in14; --visualizo en la salida el valor de la RAM
    WHEN OTHERS =>   q  <= X"00000000";
  END CASE;
  else q<= X"00000000";
   end if;
end process;

end Behavioral;