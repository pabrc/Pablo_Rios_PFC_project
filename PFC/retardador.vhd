library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Retardador is
    Port ( async_reset : in  STD_LOGIC;
           sync_reset : in  STD_LOGIC;
           clk : in  STD_LOGIC;
			  entrada: in STD_LOGIC;
           q : out  STD_LOGIC );
end Retardador;

architecture Behavioral of Retardador is

signal cont: std_logic_vector(15 downto 0);
signal econt:std_logic;

begin

	process (clk,async_reset,sync_reset,entrada)
		begin
				if async_reset='1' then
					q <='0';
					econt<='0';
					cont	<=	x"0000";
				elsif (clk'event and clk='1') then
						if sync_reset='1' then
						q <= '0';
						econt<='0';
						cont	<=	x"0000";
						else						
								if entrada ='1' then
									q <= '0';
									cont <=x"0000";
									econt<=  '1';
								end if;
								if econt= '1' then 
									if cont = x"01F4" then
										q<='1';
										cont<=cont+1;
									elsif cont =x"01F5" then 
										q		<= '0';
										cont	<=	x"0000";
									else 
										cont<=cont+1;
									end if;
								else
									q <= '0';								
																							       
								end if;
						end if;
				

				end if;

end process;


end Behavioral;