LIBRARY ieee;
--use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY Test_Chemindonnes IS
END Test_Chemindonnes;
 
ARCHITECTURE behavior OF Test_Chemindonnes IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT chemindonnees
    PORT(
         CLK : IN  std_logic;
         RST  : IN  std_logic;
         AOUT   : OUT  std_logic_vector(7 downto 0);
         BOUT : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal RST  : std_logic := '0';

 	--Outputs
   signal AOUT : std_logic_vector(7 downto 0);
   signal BOUT : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: chemindonnees PORT MAP (
          CLK => CLK,
          RST  => RST ,
          AOUT => AOUT,
          BOUT => BOUT
        );

   -- Clock process definitions
	CLK <= not clk after 2 ns;
	RST <= '0', '1' after 20 ns;
	
END;
