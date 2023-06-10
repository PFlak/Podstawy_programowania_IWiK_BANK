export interface User {
  password?: string;
  name: string;
  surname: string;
  mail: string;
  personalCode: number;
  phoneNumber: number;
  role?: 'USER' | 'ADMIN' | 'READER';
}