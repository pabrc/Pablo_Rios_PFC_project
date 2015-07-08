library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;



entity det_r is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           c : out  STD_LOGIC);
end det_r;

architecture Behavioral of det_r is

begin

	process (a,b)
		
		begin
	  
			if (a='1') then
				c<='0';
			elsif(b='1') then
				c<='1';
			end if;
		end process;
end Behavioral;
