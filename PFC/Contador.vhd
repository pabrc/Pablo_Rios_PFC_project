library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Contador is
    Port ( en : in  STD_LOGIC;
           async_reset : in  STD_LOGIC;
           sync_reset : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           q : out  STD_LOGIC_VECTOR(3 downto 0));
end Contador;

architecture Behavioral of Contador is

signal estado: std_logic_vector(3 downto 0);

begin

	q <= estado;

	process (clk,async_reset,sync_reset,en,estado)
		begin
				if async_reset='1' then
					estado <= "0000";
				elsif (clk'event and clk='1') then
						if sync_reset='1' then
						estado<= "0000";
						elsif en = '1' then
						
								if estado = "1111" then estado <= "0000";
								else   estado <= estado + 1;
						
									       
						end if;
				end if;
				

end if;

end process;


end Behavioral;