/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: MIMXRT1176xxxxx
package_id: MIMXRT1176DVMAA
mcu_data: ksdk2_0
processor_version: 12.0.0
pin_labels:
- {pin_num: K17, pin_signal: GPIO_AD_30, label: DISP_BL, identifier: DISP_BL}
- {pin_num: R13, pin_signal: GPIO_AD_02, label: DISP_RST, identifier: DISP_RST}
- {pin_num: A4, pin_signal: GPIO_DISP_B2_15, label: DISP_POWER, identifier: DISP_POWER}
- {pin_num: L14, pin_signal: GPIO_AD_26, label: CAMERA_PWDN, identifier: CAMERA_PWDN}
- {pin_num: A7, pin_signal: GPIO_DISP_B2_14, label: CAMERA_RST, identifier: CAMERA_RST}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitLpuartPins();
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLpuartPins:
- options: {callFromInitBoot: 'true', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: M15, peripheral: LPUART1, signal: RXD, pin_signal: GPIO_AD_25}
  - {pin_num: L13, peripheral: LPUART1, signal: TXD, pin_signal: GPIO_AD_24}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLpuartPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLpuartPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 is configured as LPUART1_TXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 is configured as LPUART1_RXD */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 is configured as LPUART1_RXD */
        1U);                                    /* Software Input On Field: Force input path of pad GPIO_AD_25 */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AD_24_LPUART1_TXD,          /* GPIO_AD_24 PAD functional properties : */
        0x06U);                                 /* Slew Rate Field: Slow Slew Rate
                                                   Drive Strength Field: high drive strength
                                                   Pull / Keep Select Field: Pull Enable
                                                   Pull Up / Down Config. Field: Weak pull down
                                                   Open Drain Field: Disabled
                                                   Domain write protection: Both cores are allowed
                                                   Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AD_25_LPUART1_RXD,          /* GPIO_AD_25 PAD functional properties : */
        0x06U);                                 /* Slew Rate Field: Slow Slew Rate
                                                   Drive Strength Field: high drive strength
                                                   Pull / Keep Select Field: Pull Enable
                                                   Pull Up / Down Config. Field: Weak pull down
                                                   Open Drain Field: Disabled
                                                   Domain write protection: Both cores are allowed
                                                   Domain write protection lock: Neither of DWP bits is locked */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitEnetPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: U5, peripheral: GPIO12, signal: 'gpio_io, 12', pin_signal: GPIO_LPSR_12, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: P17, peripheral: GPIO3, signal: 'gpio_mux_io, 11', pin_signal: GPIO_AD_12, direction: INPUT, gpio_interrupt: kGPIO_IntLowLevel}
  - {pin_num: K16, peripheral: ENET, signal: enet_mdc, pin_signal: GPIO_AD_32}
  - {pin_num: H17, peripheral: ENET, signal: enet_mdio, pin_signal: GPIO_AD_33}
  - {pin_num: E9, peripheral: ENET, signal: 'enet_tdata, 00', pin_signal: GPIO_DISP_B2_02}
  - {pin_num: D7, peripheral: ENET, signal: 'enet_tdata, 01', pin_signal: GPIO_DISP_B2_03}
  - {pin_num: C7, peripheral: ENET, signal: enet_tx_en, pin_signal: GPIO_DISP_B2_04}
  - {pin_num: C9, peripheral: ENET, signal: enet_ref_clk, pin_signal: GPIO_DISP_B2_05, direction: OUTPUT, software_input_on: Enable, slew_rate: Fast}
  - {pin_num: C6, peripheral: ENET, signal: 'enet_rdata, 00', pin_signal: GPIO_DISP_B2_06}
  - {pin_num: D6, peripheral: ENET, signal: 'enet_rdata, 01', pin_signal: GPIO_DISP_B2_07}
  - {pin_num: B5, peripheral: ENET, signal: enet_rx_en, pin_signal: GPIO_DISP_B2_08}
  - {pin_num: D8, peripheral: ENET, signal: enet_rx_er, pin_signal: GPIO_DISP_B2_09}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitEnetPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitEnetPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */
  CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);      /* LPCG on: LPCG is ON. */

  /* GPIO configuration of PHY_INTR on GPIO_AD_12 (pin P17) */
  gpio_pin_config_t PHY_INTR_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_IntLowLevel
  };
  /* Initialize GPIO functionality on GPIO_AD_12 (pin P17) */
  GPIO_PinInit(GPIO3, 11U, &PHY_INTR_config);
  /* Enable GPIO pin interrupt on GPIO_AD_12 (pin P17) */
  GPIO_PortEnableInterrupts(GPIO3, 1U << 11U);

  /* GPIO configuration of PHY_RESET on IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_12 (pin U5) */
  gpio_pin_config_t PHY_RESET_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO_LPSR_12 (pin U5) */
  GPIO_PinInit(GPIO12, 12U, &PHY_RESET_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_12_GPIO_MUX3_IO11,       /* GPIO_AD_12 is configured as GPIO_MUX3_IO11 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_32_ENET_MDC,             /* GPIO_AD_32 is configured as ENET_MDC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_33_ENET_MDIO,            /* GPIO_AD_33 is configured as ENET_MDIO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00,  /* GPIO_DISP_B2_02 is configured as ENET_TX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01,  /* GPIO_DISP_B2_03 is configured as ENET_TX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN,      /* GPIO_DISP_B2_04 is configured as ENET_TX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK,    /* GPIO_DISP_B2_05 is configured as ENET_REF_CLK */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_DISP_B2_05 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00,  /* GPIO_DISP_B2_06 is configured as ENET_RX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01,  /* GPIO_DISP_B2_07 is configured as ENET_RX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN,      /* GPIO_DISP_B2_08 is configured as ENET_RX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER,      /* GPIO_DISP_B2_09 is configured as ENET_RX_ER */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_GPR->GPR4 = ((IOMUXC_GPR->GPR4 &
    (~(IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK))) /* Mask bits to zero which are setting */
      | IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR(0x01U) /* ENET_REF_CLK direction control: 0x01U */
    );
  IOMUXC_GPR->GPR42 = ((IOMUXC_GPR->GPR42 &
    (~(BOARD_INITENETPINS_IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW_MASK))) /* Mask bits to zero which are setting */
      | IOMUXC_GPR_GPR42_GPIO_MUX3_GPIO_SEL_LOW(0x00U) /* GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function: 0x00U */
    );
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_12_GPIO12_IO12,        /* GPIO_LPSR_12 is configured as GPIO12_IO12 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK,    /* GPIO_DISP_B2_05 PAD functional properties : */
      0x03U);                                 /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: high drive strength
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitEnet1GPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: A5, peripheral: GPIO11, signal: 'gpio_io, 14', pin_signal: GPIO_DISP_B2_13, direction: OUTPUT, gpio_init_state: 'true'}
  - {pin_num: B6, peripheral: GPIO5, signal: 'gpio_mux_io, 13', pin_signal: GPIO_DISP_B2_12, direction: INPUT, gpio_interrupt: kGPIO_IntLowLevel}
  - {pin_num: U2, peripheral: ENET_1G, signal: enet_mdc, pin_signal: GPIO_EMC_B2_19}
  - {pin_num: R3, peripheral: ENET_1G, signal: enet_mdio, pin_signal: GPIO_EMC_B2_20}
  - {pin_num: E13, peripheral: ENET_1G, signal: enet_rx_en, pin_signal: GPIO_DISP_B1_00}
  - {pin_num: D13, peripheral: ENET_1G, signal: enet_rx_clk, pin_signal: GPIO_DISP_B1_01}
  - {pin_num: D11, peripheral: ENET_1G, signal: 'enet_rdata, 00', pin_signal: GPIO_DISP_B1_02}
  - {pin_num: E11, peripheral: ENET_1G, signal: 'enet_rdata, 01', pin_signal: GPIO_DISP_B1_03}
  - {pin_num: E10, peripheral: ENET_1G, signal: 'enet_rdata, 02', pin_signal: GPIO_DISP_B1_04}
  - {pin_num: C11, peripheral: ENET_1G, signal: 'enet_rdata, 03', pin_signal: GPIO_DISP_B1_05}
  - {pin_num: D10, peripheral: ENET_1G, signal: 'enet_tdata, 03', pin_signal: GPIO_DISP_B1_06}
  - {pin_num: E12, peripheral: ENET_1G, signal: 'enet_tdata, 02', pin_signal: GPIO_DISP_B1_07}
  - {pin_num: A15, peripheral: ENET_1G, signal: 'enet_tdata, 01', pin_signal: GPIO_DISP_B1_08}
  - {pin_num: C13, peripheral: ENET_1G, signal: 'enet_tdata, 00', pin_signal: GPIO_DISP_B1_09}
  - {pin_num: B14, peripheral: ENET_1G, signal: enet_tx_en, pin_signal: GPIO_DISP_B1_10}
  - {pin_num: A14, peripheral: ENET_1G, signal: enet_tx_clk_io, pin_signal: GPIO_DISP_B1_11}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitEnet1GPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitEnet1GPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  /* GPIO configuration of PHY_INTR on GPIO_DISP_B2_12 (pin B6) */
  gpio_pin_config_t PHY_INTR_config = {
      .direction = kGPIO_DigitalInput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_IntLowLevel
  };
  /* Initialize GPIO functionality on GPIO_DISP_B2_12 (pin B6) */
  GPIO_PinInit(GPIO5, 13U, &PHY_INTR_config);
  /* Enable GPIO pin interrupt on GPIO_DISP_B2_12 (pin B6) */
  GPIO_PortEnableInterrupts(GPIO5, 1U << 13U);

  /* GPIO configuration of PHY_RESET on GPIO_DISP_B2_13 (pin A5) */
  gpio_pin_config_t PHY_RESET_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 1U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_DISP_B2_13 (pin A5) */
  GPIO_PinInit(GPIO11, 14U, &PHY_RESET_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_00_ENET_1G_RX_EN,   /* GPIO_DISP_B1_00 is configured as ENET_1G_RX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_01_ENET_1G_RX_CLK,  /* GPIO_DISP_B1_01 is configured as ENET_1G_RX_CLK */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_02_ENET_1G_RX_DATA00,  /* GPIO_DISP_B1_02 is configured as ENET_1G_RX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_03_ENET_1G_RX_DATA01,  /* GPIO_DISP_B1_03 is configured as ENET_1G_RX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_04_ENET_1G_RX_DATA02,  /* GPIO_DISP_B1_04 is configured as ENET_1G_RX_DATA02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_05_ENET_1G_RX_DATA03,  /* GPIO_DISP_B1_05 is configured as ENET_1G_RX_DATA03 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_06_ENET_1G_TX_DATA03,  /* GPIO_DISP_B1_06 is configured as ENET_1G_TX_DATA03 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_07_ENET_1G_TX_DATA02,  /* GPIO_DISP_B1_07 is configured as ENET_1G_TX_DATA02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_08_ENET_1G_TX_DATA01,  /* GPIO_DISP_B1_08 is configured as ENET_1G_TX_DATA01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_09_ENET_1G_TX_DATA00,  /* GPIO_DISP_B1_09 is configured as ENET_1G_TX_DATA00 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_10_ENET_1G_TX_EN,   /* GPIO_DISP_B1_10 is configured as ENET_1G_TX_EN */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B1_11_ENET_1G_TX_CLK_IO,  /* GPIO_DISP_B1_11 is configured as ENET_1G_TX_CLK_IO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_12_GPIO_MUX5_IO13,  /* GPIO_DISP_B2_12 is configured as GPIO_MUX5_IO13 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_13_GPIO11_IO14,     /* GPIO_DISP_B2_13 is configured as GPIO11_IO14 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_EMC_B2_19_ENET_1G_MDC,      /* GPIO_EMC_B2_19 is configured as ENET_1G_MDC */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_EMC_B2_20_ENET_1G_MDIO,     /* GPIO_EMC_B2_20 is configured as ENET_1G_MDIO */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitMipiPanelPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: K17, peripheral: GPIO9, signal: 'gpio_io, 29', pin_signal: GPIO_AD_30, direction: OUTPUT}
  - {pin_num: R13, peripheral: GPIO9, signal: 'gpio_io, 01', pin_signal: GPIO_AD_02, direction: OUTPUT}
  - {pin_num: A4, peripheral: GPIO11, signal: 'gpio_io, 16', pin_signal: GPIO_DISP_B2_15, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitMipiPanelPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitMipiPanelPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  /* GPIO configuration of DISP_RST on GPIO_AD_02 (pin R13) */
  gpio_pin_config_t DISP_RST_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_02 (pin R13) */
  GPIO_PinInit(GPIO9, 1U, &DISP_RST_config);

  /* GPIO configuration of DISP_BL on GPIO_AD_30 (pin K17) */
  gpio_pin_config_t DISP_BL_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_30 (pin K17) */
  GPIO_PinInit(GPIO9, 29U, &DISP_BL_config);

  /* GPIO configuration of DISP_POWER on GPIO_DISP_B2_15 (pin A4) */
  gpio_pin_config_t DISP_POWER_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_DISP_B2_15 (pin A4) */
  GPIO_PinInit(GPIO11, 16U, &DISP_POWER_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_02_GPIO9_IO01,           /* GPIO_AD_02 is configured as GPIO9_IO01 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_30_GPIO9_IO29,           /* GPIO_AD_30 is configured as GPIO9_IO29 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_15_GPIO11_IO16,     /* GPIO_DISP_B2_15 is configured as GPIO11_IO16 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitMipiCameraPins:
- options: {callFromInitBoot: 'false', coreID: cm7, enableClock: 'true'}
- pin_list:
  - {pin_num: L14, peripheral: GPIO9, signal: 'gpio_io, 25', pin_signal: GPIO_AD_26, direction: OUTPUT}
  - {pin_num: A7, peripheral: GPIO11, signal: 'gpio_io, 15', pin_signal: GPIO_DISP_B2_14, direction: OUTPUT}
  - {pin_num: R8, peripheral: LPI2C6, signal: SCL, pin_signal: GPIO_LPSR_07, software_input_on: Enable}
  - {pin_num: P8, peripheral: LPI2C6, signal: SDA, pin_signal: GPIO_LPSR_06, software_input_on: Enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitMipiCameraPins, assigned for the Cortex-M7F core.
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitMipiCameraPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */
  CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr);      /* LPCG on: LPCG is ON. */

  /* GPIO configuration of CAMERA_PWDN on GPIO_AD_26 (pin L14) */
  gpio_pin_config_t CAMERA_PWDN_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_AD_26 (pin L14) */
  GPIO_PinInit(GPIO9, 25U, &CAMERA_PWDN_config);

  /* GPIO configuration of CAMERA_RST on GPIO_DISP_B2_14 (pin A7) */
  gpio_pin_config_t CAMERA_RST_config = {
      .direction = kGPIO_DigitalOutput,
      .outputLogic = 0U,
      .interruptMode = kGPIO_NoIntmode
  };
  /* Initialize GPIO functionality on GPIO_DISP_B2_14 (pin A7) */
  GPIO_PinInit(GPIO11, 15U, &CAMERA_RST_config);

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_26_GPIO9_IO25,           /* GPIO_AD_26 is configured as GPIO9_IO25 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_DISP_B2_14_GPIO11_IO15,     /* GPIO_DISP_B2_14 is configured as GPIO11_IO15 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_06_LPI2C6_SDA,         /* GPIO_LPSR_06 is configured as LPI2C6_SDA */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_06 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_LPSR_07_LPI2C6_SCL,         /* GPIO_LPSR_07 is configured as LPI2C6_SCL */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_LPSR_07 */
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
