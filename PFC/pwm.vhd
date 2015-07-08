library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity pwm is
    Port ( async_reset : in  STD_LOGIC;
			  sync_reset : in  STD_LOGIC;
           en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           ton : in  STD_LOGIC_VECTOR(31 downto 0);
			  per : in  STD_LOGIC_VECTOR(31 downto 0);
			  q : out  STD_LOGIC);
           
end pwm;

architecture Behavioral of pwm is

signal tmp: std_logic_vector(31 downto 0);


begin



process (clk,async_reset,sync_reset,ton,en,per)

	begin
	if async_reset ='1' then 
      tmp <= X"00000000";
		q <= '0';
	elsif (clk'event and clk='1')  then		
				if sync_reset='1' then 			 
					tmp<= X"00000000";
					q <= '0';
				elsif en ='1' then
				
					if tmp = per then tmp <= X"00000000";
					else tmp <= tmp + 1;
					end if;
					
					if ton <= tmp then q<='0';
					else q<='1';
					end if;
				
			   end if;		
	end if;	
end process;
end Behavioral;
