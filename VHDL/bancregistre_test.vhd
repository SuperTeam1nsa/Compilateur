--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:56:51 05/21/2020
-- Design Name:   
-- Module Name:   /home/hsahraou/Bureau/4A/COMPILATEUR/Compilateur/Compilateur/VHDL/Processeur/Processeur/bancregistre_test.vhd
-- Project Name:  Processeur
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: bancregistre
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY bancregistre_test IS
END bancregistre_test;
 
ARCHITECTURE behavior OF bancregistre_test IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT bancregistre
    PORT(
         A : IN  std_logic_vector(3 downto 0);
         B : IN  std_logic_vector(3 downto 0);
         addW : IN  std_logic_vector(3 downto 0);
         W : IN  std_logic;
         Data : IN  std_logic_vector(7 downto 0);
         RST : IN  std_logic;
         CLK : IN  std_logic;
         QA : OUT  std_logic_vector(7 downto 0);
         QB : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal A : std_logic_vector(3 downto 0) := (others => '0');
   signal B : std_logic_vector(3 downto 0) := (others => '0');
   signal addW : std_logic_vector(3 downto 0) := (others => '0');
   signal W : std_logic := '0';
   signal Data : std_logic_vector(7 downto 0) := (others => '0');
   signal RST : std_logic := '0';
   signal CLK : std_logic := '0';

 	--Outputs
   signal QA : std_logic_vector(7 downto 0);
   signal QB : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: bancregistre PORT MAP (
          A => A,
          B => B,
          addW => addW,
          W => W,
          Data => Data,
          RST => RST,
          CLK => CLK,
          QA => QA,
          QB => QB
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
--   stim_proc: process
 --  begin		
  --    -- hold reset state for 100 ns.
   --   wait for 100 ns;	

    --  wait for CLK_period*10;

      -- insert stimulus here 

    --  wait;
  -- end process;

END;
