--OK

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity instructionsmemoire is
Port ( Add : in  STD_LOGIC_VECTOR (7 downto 0);
       CLK : in  STD_LOGIC;
       OUTS : out  STD_LOGIC_VECTOR (31 downto 0)); --OUT pas possible

end instructionsmemoire;

architecture Behavioral of instructionsmemoire is
--Meme methode que le banc de registre
type memoiretableau is array (range 0 downto 255) of STD_LOGIC_VECTOR(31 downto 0);
signal instmemoire : memoiretableau := (others => (others => '0'));
--:= ( "10000000000000001000000000000000","10000000000000001000000000000000",...,""); #codeOperation operandeA OperandeB OperandeC: 8x4=32

begin

instmemoire(0)<=X"06050F00"; --AFC R5 15
instmemoire(3)<= x"02020304"; -- MUL R2 R3 R4
instmemoire(4)<= x"04020304"; -- DIV R2 R3 R4
instmemoire(5)<= x"03020304"; -- SOU R2 R3 R4
instmemoire(6)<= x"07054200"; -- LOAD R5 @66 _
instmemoire(7)<= x"08420500"; -- STORE @66 R5 _
instmemoire(2)<= x"01020304"; -- ADD R2 R3 R4


--Comme pour la mémoire des données, la lecture se fera synchrone avec l'horloge CLK.
	process
	begin
		wait until CLK'event and CLK='1';
		
		OUTS <= instmemoire(to_integer(unsigned(Add)));
		
	end process;

end Behavioral;
