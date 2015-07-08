library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity Registro_32 is
    port(CLK : in std_logic;
			CLR : in std_logic;
			EN: in std_logic;
			EN_CAP:in std_logic;
         D : in std_logic_vector(31 downto 0);
			SDETR: out std_logic;
         Q : out std_logic_vector(31 downto 0));
end Registro_32;

architecture archi of Registro_32 is
    
signal tmp: std_logic_vector(31 downto 0);

begin

	process (CLK,CLR,EN,EN_CAP)
	begin
	  
		if (CLK'event and CLK='1') then
			if (CLR='1') then
				tmp <= x"00000000";
			elsif (EN='1') then
				if(EN_CAP='0') then
					tmp <= D;
					Q <= tmp;
					SDETR<='1';
				else 
					Q <= tmp;
					SDETR<='0';
				end if;
				else
					SDETR<='0';
			end if;
		end if;
  end process;
    
   
    
end archi;

		