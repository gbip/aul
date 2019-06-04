----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:01:08 04/18/2019 
-- Design Name: 
-- Module Name:    ual - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ual is
    Port ( A : in  STD_LOGIC_VECTOR (31 downto 0);
           B : in  STD_LOGIC_VECTOR (31 downto 0);
			  DATA : in STD_LOGIC_VECTOR (31 downto 0);
			  PC : in STD_LOGIC_VECTOR (31 downto 0);
           Op : in  STD_LOGIC_VECTOR (7 downto 0);
           S : out  STD_LOGIC_VECTOR (31 downto 0);
           Flags : out  STD_LOGIC_VECTOR (3 downto 0)); -- CNZV
end ual;

architecture Behavioral of ual is

	signal Sadd : STD_LOGIC_VECTOR (32 downto 0);
	signal Ssub : STD_LOGIC_VECTOR (32 downto 0);
	signal Smul : STD_LOGIC_VECTOR (63 downto 0);
	signal Sdiv : STD_LOGIC_VECTOR (32 downto 0);
	signal Snot : STD_LOGIC_VECTOR (31 downto 0);
	signal Sand : STD_LOGIC_VECTOR (31 downto 0);
	signal Sor : STD_LOGIC_VECTOR (31 downto 0);
	signal PCadd : STD_LOGIC_VECTOR (31 downto 0);
	signal PCsub : STD_LOGIC_VECTOR (31 downto 0);
	signal inf, sup, eq : STD_LOGIC;
begin

	Sadd <= ('0'&A) + ('0'&B);
	Ssub <= ('0'&A) - ('0'&B);
	PCadd <= PC + DATA ;
	PCsub <= PC - DATA + 2;
	Smul <= (A * B);
	Snot <= x"00000000" when A /= x"00000000" else x"00000001";
	Sand <= x"00000001" when (A /= x"00000000" and B /= x"00000000") else x"00000000";
	Sor <= x"00000001" when (A /= x"00000000" or B /= x"00000000") else x"00000000";
	inf <= '1' when A < B else '0';
	sup <= '1' when A > B else '0';
	eq <= '1' when A = B else '0';
	-- Sdiv <= A/B;
	with Op select
		S <= Sadd(31 downto 0) when x"02",
			Ssub(31 downto 0) when x"03",
			Smul(31 downto 0) when x"04",
			"0000000000000000000000000000000"&eq when x"08",
			"0000000000000000000000000000000"&inf when x"09",
			"0000000000000000000000000000000"&(inf or eq) when x"0A",
			"0000000000000000000000000000000"&sup when x"0B",
			"0000000000000000000000000000000"&(sup or eq) when x"0C",
			PCadd when x"0F",
      	PCadd when x"12",
			PCsub when x"10",
			PCsub when x"13",
			B when x"0E",
			B when x"11",
			Snot when x"14",
			Sand when x"15",
			Sor when x"16",
			x"00000000" when others;
			--Sdiv(31 downto 0) when x"05";
			
	-- Carry
	Flags(3) <= Sadd(32) when Op = x"02" else
						'0';
						
	-- Negative
	
	Flags(2) <= Sadd(31) when Op = x"02" else
					Ssub(31) when Op = x"03" else
					Smul(31) when Op = x"04" else
					'0';
	-- Zero
	Flags(1) <= '1' when Op = x"02" and Sadd(31 downto 0) = x"0000" else
					'1' when Op = x"03" and Ssub(31 downto 0) = x"0000" else
					'1' when Op = x"04" and Smul(31 downto 0) = x"0000" else
					'0';

	-- Overflow
	Flags(0) <= 
					-- ( -A + (-B) > 0)
					'1' when (A(31) = '1' and B(31) = '1' and Sadd(31) = '0' and Op = x"02") else
					-- ( A + B < 0)
					'1' when (A(31) = '0' and B(31) = '0' and Sadd(31) = '1' and Op = x"02") else
					-- ( A - (-B) < 0)
					'1' when (A(31) = '0' and B(31) = '1' and Ssub(31) = '1' and Op = x"03") else
					-- ( -A - B > 0)
					'1' when (A(31) = '1' and B(31) = '0' and Ssub(31) = '0' and Op = x"03") else
					'0';
	
end Behavioral;

