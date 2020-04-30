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

entity Compteur is
    Port ( Din : in  STD_LOGIC_VECTOR (15 downto 0);
           Dout : out  STD_LOGIC_VECTOR (15 downto 0);
           CK : in  STD_LOGIC;
           RST : in  STD_LOGIC;
           SENS : in  STD_LOGIC;
           LOAD : in  STD_LOGIC;
           alea : in STD_LOGIC;
           EN : in  STD_LOGIC);
end Compteur;

architecture Behavioral of Compteur is
	signal Cmpt : STD_LOGIC_VECTOR (15 downto 0):=(Others => '0');
begin
	process -- car sur synchro front montant horloge
	begin
		wait until CK'event and CK='1';
		if RST='0' then
			Cmpt<=x"0000";
		elsif LOAD='1' then
			Cmpt<=Din;
		elsif EN='0' and alea = '0' then
			if SENS='1' then
				Cmpt<=Cmpt+1;	
			else
				Cmpt<=Cmpt-1;
			end if;
		end if;
	end process;
	
	Dout <= Cmpt-1 when alea = '1' else Cmpt;
end Behavioral;
