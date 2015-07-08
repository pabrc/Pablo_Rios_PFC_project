library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Mux_in is
    Port ( async_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
           sel : in  STD_LOGIC_VECTOR (3 downto 0);
           sync_reset : in  STD_LOGIC;
           q : out  STD_LOGIC_VECTOR (11 downto 0));
end Mux_in;

architecture Behavioral of Mux_in is

begin

process (async_reset,en,sel,sync_reset)
begin
   if async_reset ='1' then   
      q <= "000000000000";
   elsif   sync_reset = '1' then 
         q<= "000000000000";
	elsif en = '1'	then 
	
		CASE sel IS
		
    WHEN  "0000"  =>  q <= "000000000001"; -- bd0
    WHEN  "0001"  =>  q <= "000000000010"; -- timer
    WHEN  "0010"  =>  q <= "000000000100"; -- periodo
    WHEN  "0011"  =>  q <= "000000001000"; -- Ton
	 WHEN  "0100"  =>  q <= "000000010000"; -- Comparacion_0
	 WHEN  "0101"  =>  q <= "000000100000"; -- Comparacion_1
	 WHEN  "0110"  =>  q <= "000001000000"; -- Comparacion_2
	 WHEN  "0111"  =>  q <= "000010000000"; -- Comparacion_3
	 WHEN  "1000"  =>  q <= "000100000000"; -- Comparacion_4
	 WHEN  "1001"  =>  q <= "001000000000"; -- periodo PWM_1
	 WHEN  "1010"  =>  q <= "010000000000"; -- Ton PWM_1
	 WHEN  "1011"	=>	 q	<= "100000000000"; -- Memoria RAM_V
	 
    WHEN OTHERS =>   q  <= "000000000000"; 
  END CASE;
else q  <= "000000000000";
   end if;
end process;

end Behavioral;