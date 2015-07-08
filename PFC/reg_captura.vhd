library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity reg_captura is
    Port ( async_reset 	: in STD_LOGIC;
			  sync_reset 	: in STD_LOGIC;
           en 				: in STD_LOGIC;
			  lec 			: in STD_LOGIC;
           clk 			: in STD_LOGIC;
           d 				: in STD_LOGIC_VECTOR(31 downto 0);
			  captura 		: in STD_LOGIC;
			  sel_r			: out	STD_LOGIC;
			  q 				: out STD_LOGIC_VECTOR(31 downto 0);
           int_salida 	: out STD_LOGIC);
end reg_captura;

architecture Behavioral of reg_captura is

--signal	tmp2: std_logic_vector(31 downto 0):=x"0000000A";
--signal 	tmp1: std_logic_vector(31 downto 0);
signal 	tmp : std_logic_vector(31 downto 0);
signal 	aux : std_logic:='0';

begin

process (clk,async_reset,sync_reset,captura,en)


	begin
	q	 <= tmp;
	sel_r <= aux;
	
	if async_reset ='1' then 
      --tmp2 <= X"00000000";
		--tmp1 <= X"00000000";
		tmp <= X"00000000";
		int_salida <= '0';
		aux <= '0';
	elsif (clk'event and clk='1')  then		
				if sync_reset='1' then 			 
					--tmp1 <= X"00000000";
					--tmp2 <= X"00000000";
					tmp <= X"00000000";
					int_salida <= '0';
					aux <= '0';
				elsif en='1' then
					if captura= '1' then 
						if lec ='0' then
							tmp<=d;
						
							if aux='1' then
								aux <= '0';
							else 
							--tmp1 <= d; --2
								aux <= '1';
							--q<= tmp1;
							end if;
							int_salida <= '1';
						end if;
					else int_salida <= '0';
					
					end if;
				
				--	if aux='0' then
				--		q <= tmp2;
				--	else
				--		q <= tmp2; --1
				--	end if;
			  end if;
	end if;	
end process;
end Behavioral;
