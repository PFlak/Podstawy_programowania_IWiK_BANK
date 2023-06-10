export interface Account {
  accountNumber: string;
  amount: number;
  currency: string;
  type?: 1 | 2 | 3;
  interestRate?: number;
}
