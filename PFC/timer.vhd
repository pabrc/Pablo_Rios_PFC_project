library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity timer is
    Port ( async_reset : in  STD_LOGIC;
			  sync_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           load : in STD_LOGIC;
           d : in  STD_LOGIC_VECTOR(31 downto 0);
           q : out  STD_LOGIC_VECTOR(31 downto 0));
          
end timer;

architecture Behavioral of timer is

signal estado: std_logic_vector(31 downto 0);

begin

q <= estado;

process (async_reset,en,clk,sync_reset,estado)

variable primera :bit := '1';

begin
   if async_reset ='1' then   
      estado <= X"00000000";
		primera := '1';
		
   elsif (clk'event and clk='1') then 
			if sync_reset = '1' then 
				estado <= X"00000000";
				primera := '1';
			
			elsif en = '1'	then
				if (primera = '1' and load = '1') then estado <= d; primera := '0';
				elsif estado = X"FFFFFFFF" and load='0' then estado <= X"00000000";
				elsif estado = X"FFFFFFFF" and load='1' then estado <= d;
				else estado <= estado + 1;
				end if;
			else 
				primera:='1';
				
				
			end if; 
   end if;
	
	
end process;

end Behavioral;


