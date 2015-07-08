library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity R_Conf is
    Port ( async_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
			  in_captura_0 : in STD_LOGIC;
			  in_captura_1 : in STD_LOGIC;
			  in_captura_2 : in STD_LOGIC;
			  in_captura_3 : in STD_LOGIC;
			  in_captura_4 : in STD_LOGIC;
			  in_comparacion_0 : in STD_LOGIC;
			  in_comparacion_1 : in STD_LOGIC;
			  in_comparacion_2 : in STD_LOGIC;
			  in_comparacion_3 : in STD_LOGIC;
			  in_comparacion_4 : in STD_LOGIC;
           d : in  STD_LOGIC_VECTOR (15 downto 0);
           sync_reset : in  STD_LOGIC;
			  q : out  STD_LOGIC_VECTOR (15 downto 0);
           captura_0 : out STD_LOGIC;
			  captura_1 : out STD_LOGIC;
			  captura_2 : out STD_LOGIC;
			  captura_3 : out STD_LOGIC;
			  captura_4 : out STD_LOGIC;
			  comparacion_0 : out STD_LOGIC;
			  comparacion_1 : out STD_LOGIC;
			  comparacion_2 : out STD_LOGIC;
			  comparacion_3 : out STD_LOGIC;
			  comparacion_4 : out STD_LOGIC
			  );
end R_Conf;

architecture Behavioral of R_Conf is

begin

process (async_reset,en,clk,d,sync_reset,in_captura_0,in_captura_1,in_captura_2,in_captura_3,in_captura_4,in_comparacion_0,in_comparacion_1,in_comparacion_2,in_comparacion_3,in_comparacion_4)
begin
   if async_reset ='1' then   
       captura_0 <= '0';captura_1 <= '0';captura_2 <= '0';captura_3 <= '0';captura_4 <= '0';
		 comparacion_0 <='0';comparacion_1 <='0';comparacion_2 <='0'; comparacion_3 <='0';comparacion_4 <='0';
		 q<= "0000000000000000";
   elsif (clk'event and clk='1') then 
      if sync_reset = '1' then 
         captura_0 <= '0';captura_1 <= '0';captura_2 <= '0';captura_3 <= '0';captura_4 <= '0';
			comparacion_0 <='0'; comparacion_1 <='0';comparacion_2 <='0';comparacion_3 <='0';comparacion_4 <='0'; 
			q<= "0000000000000000";
			elsif in_captura_0 = '1'	then 	captura_0<= '1';				
			elsif in_captura_1 = '1'	then 	captura_1<= '1';
			elsif in_captura_2 = '1'	then 	captura_2<= '1';
			elsif in_captura_3 = '1'	then 	captura_3<= '1';
			elsif in_captura_4 = '1'	then 	captura_4<= '1';
			elsif in_comparacion_0 = '1'	then 	comparacion_0 <= '1';
			elsif in_comparacion_1 = '1'	then 	comparacion_1 <= '1';
			elsif in_comparacion_2 = '1'	then 	comparacion_2 <= '1';
			elsif in_comparacion_3 = '1'	then 	comparacion_3 <= '1';
			elsif in_comparacion_4 = '1'	then 	comparacion_4 <= '1';
			elsif en ='1' then
			q(0) <= d(0);
			q(1) <= d(1);
			q(2) <= d(2);
			q(3) <= d(3);
			q(4) <= d(4);
			q(5) <= d(5);
			q(6) <= d(6);
			q(7) <= d(7);
			q(8) <= d(8);
			q(9) <= d(9);
			q(10) <= d(10);
			q(11) <= d(11);
			q(12) <= d(12);
			q(13) <= d(13);
			q(14) <= d(14);
			q(15) <= d(15);
			
			captura_0 <= d(6);
			captura_1 <= d(7);
			captura_2 <= d(8);
			captura_3 <= d(9);
			captura_4 <= d(10);
			comparacion_0 <= d(11);
			comparacion_1 <= d(12);
			comparacion_2 <= d(13);
			comparacion_3 <= d(14);
			comparacion_4<= d(15);


	  end if;
   end if;
end process;

end Behavioral;