  library IEEE;
  use IEEE.STD_LOGIC_1164.all;
 
     ENTITY mux_tri IS
        PORT(sel    : IN std_logic_vector(5 DOWNTO 0); 
				 en	  : IN std_logic;
             salida : OUT std_logic_vector(31 DOWNTO 0));
     END mux_tri;
 
     ARCHITECTURE synth OF mux_tri IS
	  
     BEGIN
		
		PROCESS (sel,en) IS
			BEGIN
				IF en='0' then
					salida<=x"00000000";
				else
			CASE sel IS
           WHEN "000000" => salida <= x"00000000";
           WHEN "000001" => salida <= x"00000E39";
           WHEN "000010" => salida <= x"00001C72";
           WHEN "000011" => salida <= x"00002AAA";
			  WHEN "000100" => salida <= x"000038E3";
           WHEN "000101" => salida <= x"0000471C";
           WHEN "000110" => salida <= x"00005555";
           WHEN "000111" => salida <= x"0000638D";
			  WHEN "001000" => salida <= x"000071C6";
           WHEN "001001" => salida <= x"00007FFF";
           WHEN "001010" => salida <= x"00008E38";
           WHEN "001011" => salida <= x"00009C71";
			  WHEN "001100" => salida <= x"0000AAA9";
           WHEN "001101" => salida <= x"0000B8E2";
           WHEN "001110" => salida <= x"0000C71B";
           WHEN "001111" => salida <= x"0000D554";
			  WHEN "010000" => salida <= x"0000E38C";
           WHEN "010001" => salida <= x"0000F1C5";
           WHEN "010010" => salida <= x"0000FFFE";
           WHEN "010011" => salida <= x"0000F1C5";
			  WHEN "010100" => salida <= x"0000E38C";
           WHEN "010101" => salida <= x"0000D554";
           WHEN "010110" => salida <= x"0000C71B";
           WHEN "010111" => salida <= x"0000B8E2";
			  WHEN "011000" => salida <= x"0000AAA9";
           WHEN "011001" => salida <= x"00009C71";
           WHEN "011010" => salida <= x"00008E38";
           WHEN "011011" => salida <= x"00007FFF";
			  WHEN "011100" => salida <= x"000071C6";
           WHEN "011101" => salida <= x"0000638D";
           WHEN "011110" => salida <= x"00005555";
           WHEN "011111" => salida <= x"0000471C";
			  WHEN "100000" => salida <= x"000038E3";
           WHEN "100001" => salida <= x"00002AAA";
           WHEN "100010" => salida <= x"00001C72";
           WHEN "100011" => salida <= x"00000E39";
           WHEN OTHERS => salida <= x"00000000";
         END CASE;
		 END IF;
       END PROCESS;
		
     END synth;