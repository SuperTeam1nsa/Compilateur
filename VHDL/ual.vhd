--Compilation OK

library IEEE;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ual is
    Port ( A : in  STD_LOGIC_VECTOR (7 downto 0);
           B : in  STD_LOGIC_VECTOR (7 downto 0);
           S : out  STD_LOGIC_VECTOR (7 downto 0);
           Ctrl_Alu : in  STD_LOGIC_VECTOR (2 downto 0);
           
           N : out  STD_LOGIC;
           O : out  STD_LOGIC;
           Z : out  STD_LOGIC;
           C : out  STD_LOGIC);
--Le sens des flèches N,O,Z,C sont sortant de UAL; Ctrl_Alu sont entrant de UAL)

end ual;

architecture Behavioral of ual is

signal result : STD_LOGIC_VECTOR(15 downto 0);
	
begin

    process (A,B,Ctrl_Alu,result) is -- car sur synchro front montant horloge (A VERIFIER AVEC LE PROF SI ON LE MET)
	begin
	
--Le signal Ctrl_Alu informera
--sur l’opération à réaliser : Addition, Soustraction,
--Multiplication et Division
		case Ctrl_Alu is
			when "000" => --add(+)
				result <= (x"00" & A) + (x"00" & B);
			when "001" => --mul(*)
				result <= A * B;
			when "010" => --sou(-)
				result <= (x"00" & A) - (x"00" & B);
			--when "011" => --div(/) --On ne fait pas la division cette annee

			when others =>
				result <= A * B;
        end case;    
    end process;

--Les drapeaux (flags) : N,O, Z et C représentent, respectivement, --une valeur négative en sortie (S < 0), 
--un débordement (overflow : taille de A OP B > 8 bits), --une sortie nulle (S = 0) --et la retenue (carry) de l’addition

	S <= result(7 downto 0);

	N <= result(7);
	O <= '0' when result(15 downto 8) = x"00" else '1';
	Z <= '1' when result(7 downto 0) = x"00" else '0';
	C <= '1' when result(8)='1' else '0';


end Behavioral;
