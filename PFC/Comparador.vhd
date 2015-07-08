library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Comparador is
    Port ( async_reset : in  STD_LOGIC;
			  sync_reset : in  STD_LOGIC;
			  en :in STD_LOGIC;
           dato : in  STD_LOGIC_VECTOR (31 downto 0);
			  timer : in STD_LOGIC_VECTOR (31 downto 0);
			 
			  compara_out : out STD_LOGIC;
           compara_int : out  STD_LOGIC);
end Comparador;

architecture Behavioral of Comparador is


begin

process (async_reset,en,sync_reset,dato,timer) 
	begin
	
if async_reset='1' then 
	compara_int <='0';
	compara_out <='0';
	
	
	elsif sync_reset='1' then 
	compara_int <='0';
	compara_out <='0';
	
	
		elsif en = '1' then
		
			if dato < timer then 
			compara_int <= '0';
			compara_out <= '1';
			
			elsif dato > timer then 
			compara_int <= '0';
			compara_out <= '0';
			
				else compara_int<= '1';
				compara_out <= '1';
			end if;
		
		else 		
		compara_int <='0';
		compara_out <='0';	
		
end if;

end process;

end Behavioral;

