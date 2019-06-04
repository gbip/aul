--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   14:44:03 05/10/2019
-- Design Name:   
-- Module Name:   /home/pflorenc/proco/test_core.vhd
-- Project Name:  proco
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: core
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
 
ENTITY test_core IS
END test_core;
 
ARCHITECTURE behavior OF test_core IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT core
    PORT(
         clk : IN  std_logic;
         en : IN  std_logic;
         rst : IN  std_logic;
         x_w : OUT  std_logic;
         x_data : OUT  std_logic_vector(31 downto 0);
         x_reg : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal en : std_logic := '0';
   signal rst : std_logic := '0';

 	--Outputs
   signal x_w : std_logic;
   signal x_data : std_logic_vector(31 downto 0);
   signal x_reg : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: core PORT MAP (
          clk => clk,
          en => en,
          rst => rst,
          x_w => x_w,
          x_data => x_data,
          x_reg => x_reg
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      rst <= '1';
		wait for 100 ns;	
		en <= '1';
		rst <= '0';
      wait for clk_period*10000;

      -- insert stimulus here 

      wait;
   end process;

END;
